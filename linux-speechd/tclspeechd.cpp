#include <speech-dispatcher/libspeechd.h>
#include <speech-dispatcher/speechd_types.h>
#include <tcl.h>

int say(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]);
int say_character(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]);
int stop(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]);
int set_language(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]);
int set_rate(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]);

extern "C" int Tclspeechd_Init(Tcl_Interp *interp);

SPDConnection *spdConnection;


int say(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[])
{
    if (objc != 2) return TCL_ERROR;

    const char *text = Tcl_GetStringFromObj(objv[1], NULL);
    spd_say(spdConnection, SPD_MESSAGE, text);

    return TCL_OK;
}


int say_character(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[])
{
    if (objc != 2) return TCL_ERROR;

    const char *character = Tcl_GetStringFromObj(objv[1], NULL);
    spd_char(spdConnection, SPD_MESSAGE, character);

    return TCL_OK;
}


int stop(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[])
{
    spd_cancel(spdConnection);

    return TCL_OK;
}


int set_language(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[])
{
    if (objc != 2) return TCL_ERROR;

    const char *language = Tcl_GetStringFromObj(objv[1], NULL);
    spd_set_language(spdConnection, language);

    return TCL_OK;
}


int set_rate(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[])
{
    int rate;
    if (objc != 2) return TCL_ERROR;
    Tcl_GetIntFromObj(interp, objv[1], &rate);

    if (rate > 100) {
        rate = 100;
    } else if (rate < -100) {
        rate = -100;
    }

    spd_set_voice_rate(spdConnection, rate);
    return TCL_OK;
}


int Tclspeechd_Init(Tcl_Interp *interp)
{
    spdConnection = spd_open("emacspeak", NULL, NULL, SPD_MODE_SINGLE);

    Tcl_CreateObjCommand(interp, "say", say, NULL, NULL);
    Tcl_CreateObjCommand(interp, "say_character", say_character, NULL, NULL);
    Tcl_CreateObjCommand(interp, "stop", stop, NULL, NULL);
    Tcl_CreateObjCommand(interp, "set_language", set_language, NULL, NULL);
    Tcl_CreateObjCommand(interp, "set_rate", set_rate, NULL, NULL);

    return TCL_OK;
}
