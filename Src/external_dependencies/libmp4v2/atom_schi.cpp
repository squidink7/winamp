	/*
    * The contents of this file are subject to the Mozilla Public
    * License Version 1.1 (the "License"); you may not use this file
    * except in compliance with the License. You may obtain a copy of
    * the License at http://www.mozilla.org/MPL/
    * 
    * Software distributed under the License is distributed on an "AS
    * IS" basis, WITHOUT WARRANTY OF ANY KIND, either express or
    * implied. See the License for the specific language governing
    * rights and limitations under the License.
    * 
    * The Original Code is MPEG4IP.
    * 
    * The Initial Developer of the Original Code is Cisco Systems Inc.
    * Portions created by Cisco Systems Inc. are
    * Copyright (C) Cisco Systems Inc. 2001.  All Rights Reserved.
    * 
    * Contributor(s): 
    *		Alix Marchandise-Franquet  alix@cisco.com
    *
    * SchemeInformationBox for ISMACrypt
    */
	
	#include "mp4common.h"
	
	MP4SchiAtom::MP4SchiAtom() 
: MP4Atom("schi") 
	{
// not sure if this is child atoms or table of boxes
// get clarification on spec 9.1.2.5
ExpectChildAtom("iKMS", Required, OnlyOne);
ExpectChildAtom("iSFM", Required, OnlyOne);
	}
	