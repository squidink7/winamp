	/* This file was generated by Maki Compiler, do not edit manually */
	
	#include <precomp.h>
	#include <api/api.h>
	#include <api/script/objcontroller.h>
	#include "h_grouplist.h"
	
	H_GroupList::H_GroupList(ScriptObject *o) : H_GuiObject(o) {
    inited = 0;
    obj = NULL;
    H_hook(o);
	}
	
	H_GroupList::H_GroupList() {
    inited = 0;
    obj = NULL;
	}
	
	void H_GroupList::H_hook(ScriptObject *o) {
    ASSERT(!inited);
    ScriptObjectController *controller = o->vcpu_getController();
    obj = controller->cast(o, groupListGuid);
    if (obj != o && obj != NULL)
o = obj;
    else
obj = NULL;
	
    addMonitorObject(o, &groupListGuid);
	
    int iter = WASABI_API_APP->app_getInitCount();
    if (!loaded || loaded != iter) {
loaded = 1;
    }
    inited=1;
	}
	
	H_GroupList::~H_GroupList() {
    if (!inited) return;
    WASABI_API_MAKI->maki_remDlfRef(this);
	}
	
	ScriptObject *H_GroupList::getHookedObject() {
    if (obj != NULL) return obj;
    return H_GROUPLIST_PARENT::getHookedObject();
	}
	
	int H_GroupList::eventCallback(ScriptObject *object, int dlfid, scriptVar **params, int nparams) {
    if (object != getHookedObject()) return 0;
    if (H_GROUPLIST_PARENT::eventCallback(object, dlfid, params, nparams)) return 1;
    return 0;
	}
	
	int H_GroupList::loaded=0;
	