	/* This file was generated by Maki Compiler, do not edit manually */
	
	#include <precomp.h>
	
	#include <api/script/objcontroller.h>
	#include "h_menubutton.h"
	
	H_MenuButton::H_MenuButton(ScriptObject *o) : H_GuiObject(o) {
    inited = 0;
    obj = NULL;
    H_hook(o);
	}
	
	H_MenuButton::H_MenuButton() {
    inited = 0;
    obj = NULL;
	}
	
	void H_MenuButton::H_hook(ScriptObject *o) {
    ASSERT(!inited);
    ScriptObjectController *controller = o->vcpu_getController();
    obj = controller->cast(o, menuButtonGuid);
    if (obj != o && obj != NULL)
o = obj;
    else
obj = NULL;
	
    addMonitorObject(o, &menuButtonGuid);
	
    int iter = WASABI_API_APP->app_getInitCount();
    if (!loaded || loaded != iter) {
onopenmenu_id= WASABI_API_MAKI->maki_addDlfRef(o->vcpu_getController(), L"onOpenMenu", this);
onclosemenu_id= WASABI_API_MAKI->maki_addDlfRef(o->vcpu_getController(), L"onCloseMenu", this);
onselectitem_id= WASABI_API_MAKI->maki_addDlfRef(o->vcpu_getController(), L"onSelectItem", this);
loaded = 1;
    }
    inited=1;
	}
	
	H_MenuButton::~H_MenuButton() {
    if (!inited) return;
    WASABI_API_MAKI->maki_remDlfRef(this);
	}
	
	ScriptObject *H_MenuButton::getHookedObject() {
    if (obj != NULL) return obj;
    return H_MENUBUTTON_PARENT::getHookedObject();
	}
	
	int H_MenuButton::eventCallback(ScriptObject *object, int dlfid, scriptVar **params, int nparams) {
    if (object != getHookedObject()) return 0;
    if (H_MENUBUTTON_PARENT::eventCallback(object, dlfid, params, nparams)) return 1;
    if (dlfid == onopenmenu_id) { hook_onOpenMenu(); return 1; }
    if (dlfid == onclosemenu_id) { hook_onCloseMenu(); return 1; }
    if (dlfid == onselectitem_id) { hook_onSelectItem(GET_SCRIPT_STRING(*params[0])); return 1; }
    return 0;
	}
	
	int H_MenuButton::onopenmenu_id=0;
	int H_MenuButton::onclosemenu_id=0;
	int H_MenuButton::onselectitem_id=0;
	int H_MenuButton::loaded=0;
	