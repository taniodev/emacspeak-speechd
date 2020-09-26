#include <string.h>
#include <speech-dispatcher/libspeechd.h>
#include <speech-dispatcher/speechd_types.h>
#include <tcl.h>

int pause(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]);
int resume(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]);
int say(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]);
int say_character(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]);
int stop(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]);
int set_capital_letters(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]);
int set_language(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]);
int set_output_module(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]);
int set_punctuation(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]);
int set_rate(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]);
int set_volume(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]);

extern "C" int Tclspeechd_Init(Tcl_Interp *interp);

SPDConnection *spdConnection;


int pause(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[])
{
    spd_pause(spdConnection);

    return TCL_OK;
}


int resume(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[])
{
    spd_resume(spdConnection);

    return TCL_OK;
}


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


int set_capital_letters(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[])
{
    if (objc != 2) return TCL_ERROR;
    const char *type = Tcl_GetStringFromObj(objv[1], NULL);

    if (strcmp(type, "none") == 0) {
        spd_set_capital_letters(spdConnection, SPD_CAP_NONE);
    } else if (strcmp(type, "spell") == 0) {
        spd_set_capital_letters(spdConnection, SPD_CAP_SPELL);
    } else if (strcmp(type, "icon") == 0) {
        spd_set_capital_letters(spdConnection, SPD_CAP_ICON);
    }

    return TCL_OK;
}


int set_language(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[])
{
    if (objc != 2) return TCL_ERROR;

    const char *language = Tcl_GetStringFromObj(objv[1], NULL);
    spd_set_language(spdConnection, language);

    return TCL_OK;
}


int set_output_module(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[])
{
    if (objc != 2) return TCL_ERROR;

    const char *output_module = Tcl_GetStringFromObj(objv[1], NULL);
    spd_set_output_module(spdConnection, output_module);

    return TCL_OK;
}


int set_punctuation(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[])
{
    if (objc != 2) return TCL_ERROR;
    const char *punctuation = Tcl_GetStringFromObj(objv[1], NULL);

    if (strcmp(punctuation, "none") == 0) {
        spd_set_punctuation(spdConnection, SPD_PUNCT_NONE);
    } else if (strcmp(punctuation, "some") == 0) {
        spd_set_punctuation(spdConnection, SPD_PUNCT_SOME);
    } else if (strcmp(punctuation, "all") == 0) {
        spd_set_punctuation(spdConnection, SPD_PUNCT_ALL);
    }

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


int set_volume(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[])
{
    int volume;
    if (objc != 2) return TCL_ERROR;
    Tcl_GetIntFromObj(interp, objv[1], &volume);

    if (volume > 100) {
        volume = 100;
    } else if (volume < -100) {
        volume = -100;
    }

    spd_set_volume(spdConnection, volume);
    return TCL_OK;
}


int Tclspeechd_Init(Tcl_Interp *interp)
{
    spdConnection = spd_open("emacspeak", NULL, NULL, SPD_MODE_SINGLE);

    Tcl_CreateObjCommand(interp, "pause", pause, NULL, NULL);
    Tcl_CreateObjCommand(interp, "resume", resume, NULL, NULL);
    Tcl_CreateObjCommand(interp, "say", say, NULL, NULL);
    Tcl_CreateObjCommand(interp, "say_character", say_character, NULL, NULL);
    Tcl_CreateObjCommand(interp, "stop", stop, NULL, NULL);
    Tcl_CreateObjCommand(interp, "set_capital_letters", set_capital_letters, NULL, NULL);
    Tcl_CreateObjCommand(interp, "set_language", set_language, NULL, NULL);
    Tcl_CreateObjCommand(interp, "set_output_module", set_output_module, NULL, NULL);
    Tcl_CreateObjCommand(interp, "set_punctuation", set_punctuation, NULL, NULL);
    Tcl_CreateObjCommand(interp, "set_rate", set_rate, NULL, NULL);
    Tcl_CreateObjCommand(interp, "set_volume", set_volume, NULL, NULL);

    return TCL_OK;
}
