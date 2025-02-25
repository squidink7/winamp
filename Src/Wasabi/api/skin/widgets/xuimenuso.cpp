	// ----------------------------------------------------------------------------
	// Generated by ScriptObjectFactory [Sun Dec 14 07:21:52 2003]
	// 
	// File        : xuimenuso.cpp
	// Class       : XuiMenuScriptObject
	// class layer : Automatic Object Scripting
	// ----------------------------------------------------------------------------
	#include <precomp.h>
	
	#include "xuimenuso.h"
	#include "xuimenu.h"
	
	// ScriptController Instance
	static XuiMenuScriptController _xuiMenuScriptController;XuiMenuScriptController *xuiMenuScriptController = &_xuiMenuScriptController;
	
	// Function Descriptor Table
	function_descriptor_struct XuiMenuScriptController::exportedFunctions[] =  {
    {L"setMenuGroup", 1, script_setMenuGroup },
    {L"getMenuGroup", 0, script_getMenuGroup },
    {L"setMenu", 1, script_setMenu },
    {L"getMenu", 0, script_getMenu },
    {L"spawnMenu", 1, script_spawnMenu },
    {L"cancelMenu", 0, script_cancelMenu },
    {L"setNormalId", 1, script_setNormalId },
    {L"setDownId", 1, script_setDownId },
    {L"setHoverId", 1, script_setHoverId },
    {L"onOpenMenu", 0, script_onOpenMenu },
    {L"onCloseMenu", 0, script_onCloseMenu },
    {L"nextMenu", 0, script_nextMenu },
    {L"previousMenu", 0, script_previousMenu },
	};
	
	// Script Object Methods
	XuiMenuScriptObject::XuiMenuScriptObject()  {
    if (!getScriptObject()) return;
    xuiMenuScriptObject_init();
	}
	
	XuiMenuScriptObject::~XuiMenuScriptObject() {
	}
	
	void XuiMenuScriptObject::xuiMenuScriptObject_init()  {
    // Assign the script interface to this instance.
    getScriptObject()->vcpu_setInterface(XuiMenuScriptGuid, (void *)static_cast<XuiMenu*>(this));
    // Assign the class name to this instance.
    getScriptObject()->vcpu_setClassName(L"Menu");
    // Assign the controller instance to this script object instance.
    getScriptObject()->vcpu_setController(xuiMenuScriptController);
	}
	
	// Script Object Methods
	
	void XuiMenuScriptObject::script_onOpenMenu() {
    XuiMenuScriptController::script_onOpenMenu(SCRIPT_CALL, getScriptObject());
	}
	
	void XuiMenuScriptObject::script_onCloseMenu() {
    XuiMenuScriptController::script_onCloseMenu(SCRIPT_CALL, getScriptObject());
	}
	
	scriptVar /*void */ XuiMenuScriptController::script_setMenuGroup(SCRIPT_FUNCTION_PARAMS, ScriptObject *_pSO, scriptVar /*const char **/ mg) {
    // Begin all script methods with the init block.
    SCRIPT_FUNCTION_INIT;
    // Find the proper pointer for the "this" object, _pSO.
    XuiMenu*_pObj = static_cast<XuiMenu*>(_pSO->vcpu_getInterface(XuiMenuScriptGuid));
    if (_pObj) {
// Then properly call the hosted object;
_pObj->setMenuGroup(GET_SCRIPT_STRING(mg));
    }
    RETURN_SCRIPT_VOID;
	}
	
	scriptVar /*const char **/ XuiMenuScriptController::script_getMenuGroup(SCRIPT_FUNCTION_PARAMS, ScriptObject *_pSO) {
    // Begin all script methods with the init block.
    SCRIPT_FUNCTION_INIT;
    // Find the proper pointer for the "this" object, _pSO.
    XuiMenu*_pObj = static_cast<XuiMenu*>(_pSO->vcpu_getInterface(XuiMenuScriptGuid));
	
    if (_pObj) 
return MAKE_SCRIPT_STRING(_pObj->getMenuGroup());
	
    return MAKE_SCRIPT_STRING(L"");
	}
	
	scriptVar /*void */ XuiMenuScriptController::script_setMenu(SCRIPT_FUNCTION_PARAMS, ScriptObject *_pSO, scriptVar /*const char **/ m) {
    // Begin all script methods with the init block.
    SCRIPT_FUNCTION_INIT;
    // Find the proper pointer for the "this" object, _pSO.
    XuiMenu*_pObj = static_cast<XuiMenu*>(_pSO->vcpu_getInterface(XuiMenuScriptGuid));
    if (_pObj) {
// Then properly call the hosted object;
_pObj->setMenu(GET_SCRIPT_STRING(m));
    }
    RETURN_SCRIPT_VOID;
	}
	
	scriptVar /*const char **/ XuiMenuScriptController::script_getMenu(SCRIPT_FUNCTION_PARAMS, ScriptObject *_pSO) {
    // Begin all script methods with the init block.
    SCRIPT_FUNCTION_INIT;
    // Find the proper pointer for the "this" object, _pSO.
    XuiMenu*_pObj = static_cast<XuiMenu*>(_pSO->vcpu_getInterface(XuiMenuScriptGuid));
	
    if (_pObj) 
return MAKE_SCRIPT_STRING(_pObj->getMenu());
	
    return MAKE_SCRIPT_STRING(L"");
	}
	
	scriptVar /*void */ XuiMenuScriptController::script_spawnMenu(SCRIPT_FUNCTION_PARAMS, ScriptObject *_pSO, scriptVar /*int */ monitor) {
    // Begin all script methods with the init block.
    SCRIPT_FUNCTION_INIT;
    // Find the proper pointer for the "this" object, _pSO.
    XuiMenu*_pObj = static_cast<XuiMenu*>(_pSO->vcpu_getInterface(XuiMenuScriptGuid));
    if (_pObj) {
// Then properly call the hosted object;
_pObj->spawnMenu(GET_SCRIPT_INT(monitor));
    }
    RETURN_SCRIPT_VOID;
	}
	
	scriptVar /*void */ XuiMenuScriptController::script_cancelMenu(SCRIPT_FUNCTION_PARAMS, ScriptObject *_pSO) {
    // Begin all script methods with the init block.
    SCRIPT_FUNCTION_INIT;
    // Find the proper pointer for the "this" object, _pSO.
    XuiMenu*_pObj = static_cast<XuiMenu*>(_pSO->vcpu_getInterface(XuiMenuScriptGuid));
    if (_pObj) {
// Then properly call the hosted object;
_pObj->cancelMenu();
    }
    RETURN_SCRIPT_VOID;
	}
	
	scriptVar /*void */ XuiMenuScriptController::script_setNormalId(SCRIPT_FUNCTION_PARAMS, ScriptObject *_pSO, scriptVar /*const char **/ id) {
    // Begin all script methods with the init block.
    SCRIPT_FUNCTION_INIT;
    // Find the proper pointer for the "this" object, _pSO.
    XuiMenu*_pObj = static_cast<XuiMenu*>(_pSO->vcpu_getInterface(XuiMenuScriptGuid));
    if (_pObj) 
{
// Then properly call the hosted object;
_pObj->setNormalId(GET_SCRIPT_STRING(id));
    }
    RETURN_SCRIPT_VOID;
	}
	
	scriptVar /*void */ XuiMenuScriptController::script_setDownId(SCRIPT_FUNCTION_PARAMS, ScriptObject *_pSO, scriptVar /*const char **/ id) {
    // Begin all script methods with the init block.
    SCRIPT_FUNCTION_INIT;
    // Find the proper pointer for the "this" object, _pSO.
    XuiMenu*_pObj = static_cast<XuiMenu*>(_pSO->vcpu_getInterface(XuiMenuScriptGuid));
    if (_pObj) {
// Then properly call the hosted object;
_pObj->setDownId(GET_SCRIPT_STRING(id));
    }
    RETURN_SCRIPT_VOID;
	}
	
	scriptVar /*void */ XuiMenuScriptController::script_setHoverId(SCRIPT_FUNCTION_PARAMS, ScriptObject *_pSO, scriptVar /*const char **/ id) {
    // Begin all script methods with the init block.
    SCRIPT_FUNCTION_INIT;
    // Find the proper pointer for the "this" object, _pSO.
    XuiMenu*_pObj = static_cast<XuiMenu*>(_pSO->vcpu_getInterface(XuiMenuScriptGuid));
    if (_pObj) {
// Then properly call the hosted object;
_pObj->setHoverId(GET_SCRIPT_STRING(id));
    }
    RETURN_SCRIPT_VOID;
	}
	
	scriptVar /*void */ XuiMenuScriptController::script_onOpenMenu(SCRIPT_FUNCTION_PARAMS, ScriptObject *_pSO) {
    // Begin all script methods with the init block
    SCRIPT_FUNCTION_INIT;
    // Honnor C++ hooks
    PROCESS_HOOKS0(_pSO, xuiMenuScriptController);
    // If there are no script hooks to execute, we abort here.
    SCRIPT_FUNCTION_CHECKABORTEVENT;
    // Otherwise we execute the script methods by calling this.
    SCRIPT_EXEC_EVENT0(_pSO);
	}
	
	scriptVar /*void */ XuiMenuScriptController::script_onCloseMenu(SCRIPT_FUNCTION_PARAMS, ScriptObject *_pSO) {
    // Begin all script methods with the init block
    SCRIPT_FUNCTION_INIT;
    // Honnor C++ hooks
    PROCESS_HOOKS0(_pSO, xuiMenuScriptController);
    // If there are no script hooks to execute, we abort here.
    SCRIPT_FUNCTION_CHECKABORTEVENT;
    // Otherwise we execute the script methods by calling this.
    SCRIPT_EXEC_EVENT0(_pSO);
	}
	
	scriptVar /*void */ XuiMenuScriptController::script_nextMenu(SCRIPT_FUNCTION_PARAMS, ScriptObject *_pSO) {
    // Begin all script methods with the init block.
    SCRIPT_FUNCTION_INIT;
    // Find the proper pointer for the "this" object, _pSO.
    XuiMenu*_pObj = static_cast<XuiMenu*>(_pSO->vcpu_getInterface(XuiMenuScriptGuid));
    if (_pObj) {
// Then properly call the hosted object;
_pObj->nextMenu();
    }
    RETURN_SCRIPT_VOID;
	}
	
	scriptVar /*void */ XuiMenuScriptController::script_previousMenu(SCRIPT_FUNCTION_PARAMS, ScriptObject *_pSO) {
    // Begin all script methods with the init block.
    SCRIPT_FUNCTION_INIT;
    // Find the proper pointer for the "this" object, _pSO.
    XuiMenu*_pObj = static_cast<XuiMenu*>(_pSO->vcpu_getInterface(XuiMenuScriptGuid));
    if (_pObj) {
// Then properly call the hosted object;
_pObj->previousMenu();
    }
    RETURN_SCRIPT_VOID;
	}
	
	// Script Controller 
	
	// This method returns the human readable name of the class in script files.
	const wchar_t *XuiMenuScriptController::getClassName() {
    return L"Menu";
	}
	
	// This method returns the human readable name of the parent of this class.
	const wchar_t *XuiMenuScriptController::getAncestorClassName() {
    return XUIMENU_SCRIPTPARENTCLASS;
	}
	
	// This method returns the controller object for the parent class.
	ScriptObjectController *XuiMenuScriptController::getAncestorController() {
    return WASABI_API_MAKI->maki_getController(guiObjectGuid);
	}
	
	// This method returns the number of methods this class publishes.
	int XuiMenuScriptController::getNumFunctions() {
    return sizeof(exportedFunctions) / sizeof(function_descriptor_struct);
	}
	
	// This method returns the block of published function descriptors.
	const function_descriptor_struct *XuiMenuScriptController::getExportedFunctions() {
    return exportedFunctions;
	}
	
	// This method returns the GUID assigned to this script class.
	GUID XuiMenuScriptController::getClassGuid() {
    return XuiMenuScriptGuid;
	}
	
	// This method creates and returns a new script class instance.
	ScriptObject *XuiMenuScriptController::instantiate() {
    XuiMenu*_pObj = new XuiMenu();
    ASSERT(_pObj != NULL);
    return _pObj->XuiMenuScriptObject::getScriptObject();
	}
	
	// This method deletes a given script class instance.
	void XuiMenuScriptController::destroy(ScriptObject *o) {
    XuiMenu*_pObj = static_cast<XuiMenu*>(o->vcpu_getInterface(XuiMenuScriptGuid));
    ASSERT(_pObj != NULL);
    delete _pObj;
	}
	
	// This method returns an encapsulated interface for the given instance.
	void *XuiMenuScriptController::encapsulate(ScriptObject *o) {
    // No automatic encapsulation
    return NULL;
	}
	
	// This method frees a previously encapsulated interface.
	void XuiMenuScriptController::deencapsulate(void *o) {
	}
	
	