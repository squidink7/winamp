/* This file was generated by Maki Compiler, do not edit manually */

#ifndef __HOOK_CHECKBOX_H
#define __HOOK_CHECKBOX_H

#include "h_guiobject.h"

#define H_CHECKBOX_PARENT H_GuiObject

class H_CheckBox : public H_CHECKBOX_PARENT {

public:

H_CheckBox(ScriptObject *o);
H_CheckBox();
virtual ~H_CheckBox();
virtual void H_hook(ScriptObject *o);
ScriptObject *getHookedObject();

virtual int eventCallback(ScriptObject *object, int dlfid, scriptVar **params, int nparams);
virtual void hook_onToggle(int newstate) {  }

private:

ScriptObject *obj;
int inited;
static int loaded;
static int ontoggle_id;
};

#endif
