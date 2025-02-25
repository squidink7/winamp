				#include <precomp.h>
				
				#include "config.h"
				#include <bfc/pair.h>
				#include <bfc/ptrlist.h>
				#include <bfc/parse/pathparse.h>
				#include <api/xml/xmlwrite.h>
				
				#include "../xml/ifc_xmlreadercallbackI.h"
				#include "../xml/obj_xml.h"
				#include <bfc/string/url.h>
				#include <api/service/waservicefactory.h>
				
				static StringW iniFile;
				#define XNFNAME L"studio.xnf"
				
				class StringPairCompare
				{
				public:
                static int compareItem(StringPair *p1, StringPair *p2)
                {
            int r = wcscmp(p1->a.getValue(), p2->a.getValue());
            if (r == 0)
	return CMP3(p1, p2);
            else 
	return r;
                }
                static int compareAttrib(const wchar_t *attrib, StringPair *item)
                {
            return wcscmp(attrib, item->a.getValue());
                }
				};
				
				static PtrListQuickSorted<StringPair, StringPairCompare> strings;
				
				class Reader : public ifc_xmlreadercallbackI
				{
				public:
                ~Reader();
                void xmlReaderOnStartElementCallback(const wchar_t *xmlpath, const wchar_t *xmltag, ifc_xmlreaderparams *params);
                void xmlReaderOnEndElementCallback(const wchar_t *xmlpath, const wchar_t *xmltag);
				
                void readem();
				
				private:
                PtrList<StringW> sections;
				};
				
				Reader::~Reader()
				{
                sections.deleteAll();
				}
				
				void Reader::xmlReaderOnStartElementCallback(const wchar_t *xmlpath, const wchar_t *xmltag, ifc_xmlreaderparams *params)
				{
                if (!WCSICMP(xmltag, L"section"))
                {
            const wchar_t *name = params->getItemValue(L"name");
            if (name == NULL) 
            return ;
				
            StringW *strName = new StringW(name);
            Url::decode(*strName);
            sections.addItem(strName);
                }
                else if (!WCSICMP(xmltag, L"entry"))
                {
            const wchar_t *name = params->getItemValue(L"name");
            const wchar_t *value = params->getItemValue(L"value");
				
            // just in case
            if (!WCSICMP(name, L"(null)")) name = NULL;
            if (!WCSICMP(value, L"(null)")) value = NULL;
				
            if (name == NULL /*| !*name */ || value == NULL /*|| !*value*/) return ;
            StringW strName = name;
            Url::decode(strName);
				
		StringW strValue = value;
            Url::decode(strValue);
				
            StringW n;
            for (int i = 0; i < sections.getNumItems(); i++)
            {
            n.catPostSeparator(*sections[i], '/');
            }
            n += strName;
            
            StringPair *p = new StringPair(n, strValue);
            strings.addItem(p);
                }
				}
				
				void Reader::xmlReaderOnEndElementCallback(const wchar_t *xmlpath, const wchar_t *xmltag)
				{
                if (!WCSICMP(xmltag, L"section"))
                {
            StringW *last = sections.getLast();
            sections.removeLastItem();
            delete last;
                }
				}
				
				void LoadXmlFile(obj_xml *parser, const wchar_t *filename);
				
				void Reader::readem()
				{
                strings.deleteAll();
                
                if (iniFile.isempty())
                {   
            iniFile = StringPathCombine(WASABI_API_APP->path_getUserSettingsPath(), XNFNAME);
                }
				
                waServiceFactory *parserFactory = WASABI_API_SVC->service_getServiceByGuid(obj_xmlGUID);
                if (parserFactory)
                {
            obj_xml *parser = (obj_xml *)parserFactory->getInterface();
				
            if (parser)
            {
				
            parser->xmlreader_registerCallback(L"WinampXML\fconfiguration\f*", this);
            parser->xmlreader_registerCallback(L"WasabiXML\fconfiguration\f*", this);
            parser->xmlreader_open();
            LoadXmlFile(parser, iniFile);
				
            parser->xmlreader_unregisterCallback(this);
            parser->xmlreader_close();
            parserFactory->releaseInterface(parser);
            parser = 0;
            }
                }
				}
				
				StringPair *ConfigFile::getPair(const wchar_t *name)
				{
                ASSERT(!sectionname.isempty());
			StringW nname;
		nname.catPostSeparator(sectionname.getValue(), '/');
		nname.cat(name);
                return strings.findItem(nname.getValue()); // cast to make PtrListSorted happy
				}
				
				StringPair *ConfigFile::makePair(const wchar_t *name, const wchar_t *value)
				{
                StringPair *ret = getPair(name);
                if (ret == NULL)
                {
		StringW nname;
		nname.catPostSeparator(sectionname.getValue(), '/');
		nname.cat(name);
				
            ret = new StringPair(nname, value);
            strings.addItem(ret);
                }
                else
                {
            ret->b.setValue(value);
                }
                return ret;
				}
				
				static int ninstances, inited;
				
				ConfigFile::ConfigFile(const wchar_t *section, const wchar_t *name)
				{
                sectionname = section;
                prettyname = name;
                ninstances++;
				}
				
				void ConfigFile::initialize()
				{
                Reader().readem();
				}
				
				ConfigFile::~ConfigFile()
				{
                ninstances--;
                if (ninstances == 0)
                {
            FILE *fp = _wfopen(iniFile, WF_WRITE_TEXT);
            if (fp != NULL)
            {
            // write out the file
            XMLWrite xml(fp, L"WasabiXML");
            const wchar_t *app = WASABI_API_APP->main_getVersionString();
            if (!app) 
app = L"thousands of irascible butt monkeys";
            xml.comment(StringPrintfW(L"Generated by: %s (%d)", app, WASABI_API_APP->main_getBuildNumber()));
            xml.pushCategory(L"configuration");
				
            PtrList<StringW> cats;
				
            for (int i = 0; i < strings.getNumItems(); i++)
            {
        StringPair *p = strings[i];
        PathParserW pp(p->a);
				
        int climit = MIN(pp.getNumStrings() - 1, cats.getNumItems());
        int j;
        for (j = 0; j < climit; j++)
        {
        if (WCSICMP(*cats[j], pp.enumString(j)))
        {
    climit = j;
    break;
        }
        }
				
        while (cats.getNumItems() > climit)
        {
        StringW *s = cats.getLast();
        xml.popCategory();
        cats.removeLastItem();
        delete s;
        }
        for (j = climit; j < pp.getNumStrings() - 1; j++)
        {
        StringW *s = cats.addItem(new StringW(pp.enumString(j)));
        xml.pushCategoryAttrib(L"section");
        StringW enc = *s;
        Url::encode(enc, FALSE, URLENCODE_EXCLUDE_ABOVEEQ32);
        xml.writeCategoryAttrib(L"name", enc);
        xml.closeCategoryAttrib();
        }
				
        xml.pushCategoryAttrib(L"entry", TRUE);
        StringW enc = pp.getLastString();
        Url::encode(enc, FALSE, URLENCODE_EXCLUDE_ABOVEEQ32);
        xml.writeCategoryAttrib(L"name", enc);
        enc = p->b;
        Url::encode(enc, FALSE, URLENCODE_EXCLUDE_ABOVEEQ32);
        if (enc.iscaseequal(L"(null)") || enc.getValue() == NULL)
        enc.setValue(L"");
        xml.writeCategoryAttrib(L"value", enc);
        xml.closeCategoryAttrib();
        xml.popCategory();
            }
				
            while (xml.popCategory()) ;
				
            strings.deleteAll();
            fclose(fp);
            } // fp != NULL
                }	// ninstances==0
				}
				
				int verifyName(const wchar_t *str)
				{
                for (const wchar_t *p = str; *p; p++)
                {
            if (!ISALPHA(*p) &&
            !ISDIGIT(*p) &&
            !ISPUNCT(*p) &&
            !ISSPACE(*p) &&
            *p != '|' && *p != '_')
            return 0;
                }
                return 1;
				}
				
				void ConfigFile::setInt(const wchar_t *name, int val)
				{
                INCRITICALSECTION(cs);
                if (name == NULL) return ;
                if (!verifyName(name))
                {
            DebugStringW(L"illegal name given\n");
            //__asm { int 3 };
            return ;
                }
                makePair(name, StringPrintfW(val));
				}
				
				int ConfigFile::getInt(const wchar_t *name, int def_val)
				{
                INCRITICALSECTION(cs);
                if (name == NULL) return def_val;
                StringPair *p = getPair(name);
                if (p == NULL) return def_val;
                return WTOI(p->b.getValue());
				}
				
				void ConfigFile::setString(const wchar_t *name, const wchar_t *str)
				{
                INCRITICALSECTION(cs);
                if (name == NULL) return ;
                if (!verifyName(name))
                {
            DebugStringW(L"illegal name given\n");
            return ;
                }
                if (str == NULL)
                {
            StringPair *p = getPair(name);
            if (p != NULL)
            {
            strings.delItem(p);
            delete p;
            return ;
            }
                }
                makePair(name, str);
				}
				
				int ConfigFile::getString(const wchar_t *name, wchar_t *buf, int buf_len, const wchar_t *def_str)
				{
                INCRITICALSECTION(cs);
                if (name == NULL || buf == NULL) return -1;
                if (def_str == NULL)
		def_str = L"";
                StringPair *p = getPair(name);
                if (p == NULL)
            WCSCPYN(buf, def_str, buf_len);
                else
            WCSCPYN(buf, p->b.getValueSafe(), buf_len);
                return 1;
				}
				
				int ConfigFile::getStringLen(const wchar_t *name)
				{
                INCRITICALSECTION(cs);
                if (name == NULL) return -1;
                StringPair *p = getPair(name);
                if (p == NULL) return -1;
                return wcslen(p->b.getValue());
				}
				