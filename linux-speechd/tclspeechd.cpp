#include <speech-dispatcher/libspeechd.h>
#include <speech-dispatcher/speechd_types.h>
#include <tcl.h>

int say(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]);

extern "C" int Tclspeechd_Init(Tcl_Interp *interp);

SPDConnection *spdConnection;


int say(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[])
{
    if (objc != 2) return TCL_ERROR;

    const char *text = Tcl_GetStringFromObj(objv[1], NULL);
    spd_say(spdConnection, SPD_MESSAGE, text);

    return TCL_OK;
}


int Tclspeechd_Init(Tcl_Interp *interp)
{
    spdConnection = spd_open("emacspeak", NULL, NULL, SPD_MODE_SINGLE);

    Tcl_CreateObjCommand(interp, "say", say, NULL, NULL);

    return TCL_OK;
}
