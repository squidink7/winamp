/* This file was generated by Maki Compiler, do not edit manually */

#ifndef __C_GUITREE_H
#define __C_GUITREE_H

#include "c_guiobject.h"

#define C_GUITREE_PARENT C_GuiObject

class C_GuiTree : public C_GUITREE_PARENT {
public:

C_GuiTree(ScriptObject *object);
C_GuiTree();
virtual ~C_GuiTree();

virtual void C_hook(ScriptObject *o);

ScriptObject *getScriptObject();

virtual int onWantAutoContextMenu();
virtual int onMouseWheelUp(int clicked, int lines);
virtual int onMouseWheelDown(int clicked, int lines);
virtual int onContextMenu(int x, int y);
virtual int onChar(int c);
virtual void onItemRecvDrop(ScriptObject *item);
virtual void onLabelChange(ScriptObject *item);
virtual void onItemSelected(ScriptObject *item);
virtual void onItemDeselected(ScriptObject *item);
virtual int getNumRootItems();
virtual ScriptObject *enumRootItem(int which);
virtual void jumpToNext(int c);
virtual void ensureItemVisible(ScriptObject *item);
virtual int getContentsWidth();
virtual int getContentsHeight();
virtual ScriptObject *addTreeItem(ScriptObject *item, ScriptObject *par, int sorted, int haschildtab);
virtual int removeTreeItem(ScriptObject *item);
virtual void moveTreeItem(ScriptObject *item, ScriptObject *newparent);
virtual void deleteAllItems();
virtual int expandItem(ScriptObject *item);
virtual void expandItemDeferred(ScriptObject *item);
virtual int collapseItem(ScriptObject *item);
virtual void collapseItemDeferred(ScriptObject *item);
virtual void selectItem(ScriptObject *item);
virtual void selectItemDeferred(ScriptObject *item);
virtual void delItemDeferred(ScriptObject *item);
virtual void hiliteItem(ScriptObject *item);
virtual void unhiliteItem(ScriptObject *item);
virtual ScriptObject *getCurItem();
virtual ScriptObject *hitTest(int x, int y);
virtual void editItemLabel(ScriptObject *item);
virtual void cancelEditLabel(int destroyit);
virtual void setAutoEdit(int ae);
virtual int getAutoEdit();
virtual ScriptObject *getByLabel(ScriptObject *item, const wchar_t *name);
virtual void setSorted(int dosort);
virtual int getSorted();
virtual void sortTreeItems();
virtual ScriptObject *getSibling(ScriptObject *item);
virtual void setAutoCollapse(int doautocollapse);
virtual int setFontSize(int newsize);
virtual int getFontSize();
virtual int getNumVisibleChildItems(ScriptObject *c);
virtual int getNumVisibleItems();
virtual ScriptObject *enumVisibleItems(int n);
virtual ScriptObject *enumVisibleChildItems(ScriptObject *c, int n);
virtual ScriptObject *enumAllItems(int n);
virtual int getItemRectX(ScriptObject *item);
virtual int getItemRectY(ScriptObject *item);
virtual int getItemRectW(ScriptObject *item);
virtual int getItemRectH(ScriptObject *item);

private:

ScriptObject *obj;
int inited;
static int loaded;
static int onwantautocontextmenu_id;
static int onmousewheelup_id;
static int onmousewheeldown_id;
static int oncontextmenu_id;
static int onchar_id;
static int onitemrecvdrop_id;
static int onlabelchange_id;
static int onitemselected_id;
static int onitemdeselected_id;
static int getnumrootitems_id;
static int enumrootitem_id;
static int jumptonext_id;
static int ensureitemvisible_id;
static int getcontentswidth_id;
static int getcontentsheight_id;
static int addtreeitem_id;
static int removetreeitem_id;
static int movetreeitem_id;
static int deleteallitems_id;
static int expanditem_id;
static int expanditemdeferred_id;
static int collapseitem_id;
static int collapseitemdeferred_id;
static int selectitem_id;
static int selectitemdeferred_id;
static int delitemdeferred_id;
static int hiliteitem_id;
static int unhiliteitem_id;
static int getcuritem_id;
static int hittest_id;
static int edititemlabel_id;
static int canceleditlabel_id;
static int setautoedit_id;
static int getautoedit_id;
static int getbylabel_id;
static int setsorted_id;
static int getsorted_id;
static int sorttreeitems_id;
static int getsibling_id;
static int setautocollapse_id;
static int setfontsize_id;
static int getfontsize_id;
static int getnumvisiblechilditems_id;
static int getnumvisibleitems_id;
static int enumvisibleitems_id;
static int enumvisiblechilditems_id;
static int enumallitems_id;
static int getitemrectx_id;
static int getitemrecty_id;
static int getitemrectw_id;
static int getitemrecth_id;
};

#endif
