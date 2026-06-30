#include <list>
#include <vector>
#include <string.h>
#include <pthread.h>
#include <thread>
#include <cstring>
#include <jni.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <dlfcn.h>
#include "Includes/Logger.h"
#include "Includes/obfuscate.h"
#include "Includes/Utils.h"
#include "KittyMemory/MemoryPatch.h"
#include "Menu/Setup.h"

//Target lib here
#define targetLibName OBFUSCATE("libil2cpp.so")

#include "Includes/Macros.h"

/*
float Your Example = 0;

float (*old_yourexample)(void *instance);
float yourexample(void *instance) {
    if (instance != NULL && Your Example > 1) {
        return (float) Your Example;
    }
    return old_yourexample(instance);
}

/*
bool (*old_get_BoolExample)(void *instance);
bool get_BoolExample(void *instance) {
    if (instance != NULL && featureHookToggle) {
        return true;
    }
    return old_get_BoolExample(instance);
}

float (*old_get_FloatExample)(void *instance);
float get_FloatExample(void *instance) {
    if (instance != NULL && sliderValue > 1) {
        return (float) sliderValue;
    }
    return old_get_FloatExample(instance);
}

int (*old_Level)(void *instance);
int Level(void *instance) {
    if (instance != NULL && level) {
        return (int) level;
    }
    return old_Level(instance);
}

void (*old_FunctionExample)(void *instance);
void FunctionExample(void *instance) {
    instanceBtn = instance;
    if (instance != NULL) {
        if (Health) {
            *(int *) ((uint64_t) instance + 0x48) = 999;
        }
    }
    return old_FunctionExample(instance);
}
*/
bool ShouldApplySkillCooldown_Enabled = false;


bool (*old_ShouldApplySkillCooldown)(void *instance);

bool ShouldApplySkillCooldown(void *instance) {
 
    if (instance != NULL && ShouldApplySkillCooldown_Enabled) {
 
	   return false; // Return false to disable the cooldown
  
     }
 
	 return old_ShouldApplySkillCooldown(instance);

}

void *hack_thread(void *) {
    LOGI(OBFUSCATE("pthread created"));

    //Check if target lib is loaded
    do {
        sleep(1);
    } while (!isLibraryLoaded(targetLibName));

    //Anti-lib rename
    /*
    do {
        sleep(1);
    } while (!isLibraryLoaded("libYOURNAME.so"));*/

    LOGI(OBFUSCATE("%s has been loaded"), (const char *) targetLibName);

#if defined(__aarch64__)

 //   HOOK_LIB("libil2cpp.so", "0x000000", yourexample, old_yourexample);
 // Asegúrate de que esto esté dentro de hack_thread
      
HOOK_LIB("libil2cpp.so", "0x7249524", ShouldApplySkillCooldown, old_ShouldApplySkillCooldown);


#else 

    LOGI(OBFUSCATE("Done"));
#endif

    //Anti-leech
    /*if (!iconValid || !initValid || !settingsValid) {
        //Bad function to make it crash
        sleep(5);
        int *p = 0;
        *p = 0;
    }*/

    return NULL;
}

// Do not change or translate the first text unless you know what you are doing
// Assigning feature numbers is optional. Without it, it will automatically count for you, starting from 0
// Assigned feature numbers can be like any numbers 1,3,200,10... instead in order 0,1,2,3,4,5...
// ButtonLink, Category, RichTextView and RichWebView is not counted. They can't have feature number assigned
// Toggle, ButtonOnOff and Checkbox can be switched on by default, if you add True_. Example: CheckBox_True_The Check Box
// To learn HTML, go to this page: https://www.w3schools.com/

jobjectArray GetFeatureList(JNIEnv *env, jobject context) {
    jobjectArray ret;

    const char *features[] = {
            OBFUSCATE("Category_Korleonne V1"), //Not case
            OBFUSCATE("Toggle_Unlimited Coins"),// case0
            OBFUSCATE("Toggle_Unlimited Gems"),// case1
            OBFUSCATE("Toggle_Unlimited Grenade"),// case2
            OBFUSCATE("Toggle_Unlimited Revive"),// case3
            OBFUSCATE("Toggle_Unlimited Energy"),// case4
            OBFUSCATE("Toggle_Unlimited Rpg Rocket"),// case5
            OBFUSCATE("Toggle_Unlimited Medkit"), // case6
			OBFUSCATE("Toggle_No Skill Cooldown"), // case7
            
           
    };

    //Now you dont have to manually update the number everytime;
    int Total_Feature = (sizeof features / sizeof features[0]);
    ret = (jobjectArray)
            env->NewObjectArray(Total_Feature, env->FindClass(OBFUSCATE("java/lang/String")),
                                env->NewStringUTF(""));

    for (int i = 0; i < Total_Feature; i++)
        env->SetObjectArrayElement(ret, i, env->NewStringUTF(features[i]));

    return (ret);
}

void Changes(JNIEnv *env, jclass clazz, jobject obj,
                                        jint featNum, jstring featName, jint value,
                                        jboolean boolean, jstring str) {

    LOGD(OBFUSCATE("Feature name: %d - %s | Value: = %d | Bool: = %d | Text: = %s"), featNum,
         env->GetStringUTFChars(featName, 0), value,
         boolean, str != NULL ? env->GetStringUTFChars(str, 0) : "");

    //BE CAREFUL NOT TO ACCIDENTLY REMOVE break;

    switch (featNum) {
		case 0:
			PATCH_LIB_SWITCH("libil2cpp.so","0x13CD3A4","A0 A2 99 D2 60 EB A0 F2 C0 03 5F D6",boolean);
			break;
		case 1:
            PATCH_LIB_SWITCH("libil2cpp.so","0x13CD4F0","A0 A2 99 D2 60 EB A0 F2 C0 03 5F D6",boolean);
			break;
        case 2:
            PATCH_LIB_SWITCH("libil2cpp.so","0x13CC998","A0 A2 99 D2 60 EB A0 F2 C0 03 5F D6",boolean);
            break;
        case 3:
            PATCH_LIB_SWITCH("libil2cpp.so","0x13CD014","A0 A2 99 D2 60 EB A0 F2 C0 03 5F D6",boolean);
			break;
        case 4:
            PATCH_LIB_SWITCH("libil2cpp.so","0x13CD1C0","A0 A2 99 D2 60 EB A0 F2 C0 03 5F D6",boolean);
            break;
        case 5:
            PATCH_LIB_SWITCH("libil2cpp.so","0x13CCCBC","A0 A2 99 D2 60 EB A0 F2 C0 03 5F D6",boolean);
            break;
        case 6:
            PATCH_LIB_SWITCH("libil2cpp.so","0x13CCE68","A0 A2 99 D2 60 EB A0 F2 C0 03 5F D6",boolean);
			break;
        case 7:
        
    ShouldApplySkillCooldown_Enabled = boolean;
 
		    break;
    }
}

__attribute__((constructor))
void lib_main() {
    // Create a new thread so it does not block the main thread, means the game would not freeze
    pthread_t ptid;
    pthread_create(&ptid, NULL, hack_thread, NULL);
}

int RegisterMenu(JNIEnv *env) {
    JNINativeMethod methods[] = {
            {OBFUSCATE("Icon"), OBFUSCATE("()Ljava/lang/String;"), reinterpret_cast<void *>(Icon)},
            {OBFUSCATE("IconWebViewData"),  OBFUSCATE("()Ljava/lang/String;"), reinterpret_cast<void *>(IconWebViewData)},
            {OBFUSCATE("IsGameLibLoaded"),  OBFUSCATE("()Z"), reinterpret_cast<void *>(isGameLibLoaded)},
            {OBFUSCATE("Init"),  OBFUSCATE("(Landroid/content/Context;Landroid/widget/TextView;Landroid/widget/TextView;)V"), reinterpret_cast<void *>(Init)},
            {OBFUSCATE("SettingsList"),  OBFUSCATE("()[Ljava/lang/String;"), reinterpret_cast<void *>(SettingsList)},
            {OBFUSCATE("GetFeatureList"),  OBFUSCATE("()[Ljava/lang/String;"), reinterpret_cast<void *>(GetFeatureList)},
    };

    jclass clazz = env->FindClass(OBFUSCATE("com/android/support/Menu"));
    if (!clazz)
        return JNI_ERR;
    if (env->RegisterNatives(clazz, methods, sizeof(methods) / sizeof(methods[0])) != 0)
        return JNI_ERR;
    return JNI_OK;
}

int RegisterPreferences(JNIEnv *env) {
    JNINativeMethod methods[] = {
            {OBFUSCATE("Changes"), OBFUSCATE("(Landroid/content/Context;ILjava/lang/String;IZLjava/lang/String;)V"), reinterpret_cast<void *>(Changes)},
    };
    jclass clazz = env->FindClass(OBFUSCATE("com/android/support/Preferences"));
    if (!clazz)
        return JNI_ERR;
    if (env->RegisterNatives(clazz, methods, sizeof(methods) / sizeof(methods[0])) != 0)
        return JNI_ERR;
    return JNI_OK;
}

int RegisterMain(JNIEnv *env) {
    JNINativeMethod methods[] = {
            {OBFUSCATE("CheckOverlayPermission"), OBFUSCATE("(Landroid/content/Context;)V"), reinterpret_cast<void *>(CheckOverlayPermission)},
    };
    jclass clazz = env->FindClass(OBFUSCATE("com/android/support/Main"));
    if (!clazz)
        return JNI_ERR;
    if (env->RegisterNatives(clazz, methods, sizeof(methods) / sizeof(methods[0])) != 0)
        return JNI_ERR;

    return JNI_OK;
}

extern "C"
JNIEXPORT jint JNICALL
JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env;
    vm->GetEnv((void **) &env, JNI_VERSION_1_6);
    if (RegisterMenu(env) != 0)
        return JNI_ERR;
    if (RegisterPreferences(env) != 0)
        return JNI_ERR;
    if (RegisterMain(env) != 0)
        return JNI_ERR;
    return JNI_VERSION_1_6;
}
