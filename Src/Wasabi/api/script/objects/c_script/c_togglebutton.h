/* This file was generated by Maki Compiler, do not edit manually */

#ifndef __C_TOGGLEBUTTON_H
#define __C_TOGGLEBUTTON_H

#include "c_button.h"

#define C_TOGGLEBUTTON_PARENT C_Button

class C_ToggleButton : public C_TOGGLEBUTTON_PARENT {
public:

C_ToggleButton(ScriptObject *object);
C_ToggleButton();
virtual ~C_ToggleButton();

virtual void C_hook(ScriptObject *o);

ScriptObject *getScriptObject();

virtual void onToggle(int (null));
virtual int getCurCfgVal();

private:

ScriptObject *obj;
int inited;
static int loaded;
static int ontoggle_id;
static int getcurcfgval_id;
};

#endif
