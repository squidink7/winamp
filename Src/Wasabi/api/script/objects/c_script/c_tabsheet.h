/* This file was generated by Maki Compiler, do not edit manually */

#ifndef __C_TABSHEET_H
#define __C_TABSHEET_H

#include "c_guiobject.h"

#define C_TABSHEET_PARENT C_GuiObject

class C_TabSheet : public C_TABSHEET_PARENT {
public:

C_TabSheet(ScriptObject *object);
C_TabSheet();
virtual ~C_TabSheet();

virtual void C_hook(ScriptObject *o);

ScriptObject *getScriptObject();

virtual int getCurPage();
virtual void setCurPage(int a);

private:

ScriptObject *obj;
int inited;
static int loaded;
static int getcurpage_id;
static int setcurpage_id;
};

#endif
