/* This file was generated by Maki Compiler, do not edit manually */

#ifndef __HOOK_DROPDOWNLIST_H
#define __HOOK_DROPDOWNLIST_H

#include "h_guiobject.h"

#define H_DROPDOWNLIST_PARENT H_GuiObject

class H_DropDownList : public H_DROPDOWNLIST_PARENT {

public:

H_DropDownList(ScriptObject *o);
H_DropDownList();
virtual ~H_DropDownList();
virtual void H_hook(ScriptObject *o);
ScriptObject *getHookedObject();

virtual int eventCallback(ScriptObject *object, int dlfid, scriptVar **params, int nparams);
virtual void hook_onSelect(int id, int hover) {  }

private:

ScriptObject *obj;
int inited;
static int loaded;
static int onselect_id;
};

#endif
