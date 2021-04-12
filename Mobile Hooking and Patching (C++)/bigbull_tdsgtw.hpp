#include <pthread.h>
#include "KittyMemory/MemoryPatch.h"
#include "KittyMemory/Logger.h"
#import "Includes/Utils.h"

#define SoFile libapp.so

int ohk = 0;
int godmode = 0;
bool silentaim = true;

bool hack1 = false, hack2 = false, hack3 = false;

extern "C" {
JNIEXPORT jboolean JNICALL
Java_uk_lgl_modmenu_FloatingModMenuService_EnableSounds(
        JNIEnv *env,
        jobject activityObject) {
    return true;
}
	
JNIEXPORT jstring JNICALL
Java_uk_lgl_modmenu_FloatingModMenuService_Title(
        JNIEnv *env,
        jobject activityObject) {
    jstring str = env->NewStringUTF("");
    return str;
}

JNIEXPORT jstring JNICALL
Java_uk_lgl_modmenu_FloatingModMenuService_Heading(
        JNIEnv *env,
        jobject activityObject) {
    std::string toast_text = "";
    return env->NewStringUTF(toast_text.c_str());
}

JNIEXPORT jstring JNICALL
Java_uk_lgl_modmenu_FloatingModMenuService_Icon(
        JNIEnv *env,
        jobject activityObject) {

    //Use https://www.base64encode.org/ to encode your image to base64

    std::string str = "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";
    return env->NewStringUTF(str.c_str());
}

JNIEXPORT jint JNICALL
Java_uk_lgl_modmenu_FloatingModMenuService_IconSize(
        JNIEnv *env,
        jobject activityObject) {
    return 70;
}

JNIEXPORT jstring JNICALL
Java_uk_lgl_modmenu_FloatingModMenuService_Toast(
        JNIEnv *env,
        jclass clazz) {

    return env->NewStringUTF("Title title");
}

int dmgmul = 1;
int defmul = 1;
JNIEXPORT void JNICALL
Java_uk_lgl_modmenu_FloatingModMenuService_Changes(
        JNIEnv *env,
        jobject activityObject,
        jint feature,
        jint value) {

    // You must count your features from 0, not 1
    switch (feature) {
		case 0: // Switch 2
			if (value >= 1)
			{
				dmgmul = value;
			}
            break;
        case 1: // Switch 2
			if (value >= 1)
			{
				defmul = value;
			}
            break;
        case 2: // Switch
			hack3 = !hack3;
            if (hack3) {
                my_cool_Patches.Patch1.Modify();
                my_cool_Patches.Patch2.Modify();
                my_cool_Patches.Patch3.Modify();
                my_cool_Patches.Patch4.Modify();
                my_cool_Patches.Patch5.Modify();
            } else {
                my_cool_Patches.Patch1.Restore();
                my_cool_Patches.Patch2.Restore();
                my_cool_Patches.Patch3.Restore();
                my_cool_Patches.Patch4.Restore();
                my_cool_Patches.Patch5.Restore();
            }
            break;
		case 3: // Switch 2
			hack1 = !hack1;
            break;
    }
}

JNIEXPORT jobjectArray JNICALL
Java_uk_lgl_modmenu_FloatingModMenuService_getFeatureList(
        JNIEnv *env,
        jobject activityObject) {
    jobjectArray ret;

    // Note: Do not translate the first text
    // Usage:
    // Category_(text)
    // Toggle_[feature name]
    // SeekBar_[feature name]_[min value]_[max value]
    // Spinner_[feature name]_[Items e.g. item1_item2_item3]
    // Button_[feature name]
    // Button_OnOff_[feature name]
    // InputValue_[feature name]
    const char *features[] = {
            "SeekBar_DMG multiplier_0_500",
            "SeekBar_DEF multiplier_0_500",
            "Toggle_Freeze monsters",
			"Toggle_No cooldown"}; 

    int Total_Feature = (sizeof features /
                         sizeof features[0]); //Now you dont have to manually update the number everytime;

    ret = (jobjectArray) env->NewObjectArray(Total_Feature, env->FindClass("java/lang/String"),
                                             env->NewStringUTF(""));
    int i;
    for (i = 0; i < Total_Feature; i++)
        env->SetObjectArrayElement(ret, i, env->NewStringUTF(features[i]));
    return (ret);
}

}

#define libName O("libil2cpp.so")

bool (*get_IsMyTeam)(void *_this) = (bool(*)(void *)) getAbsoluteAddress(libName, 0x47C2F8); 

void (*orig_ModifyHp)(void *_this, int value);
void ModifyHp(void* _this, int value) {
	if(_this != NULL)
	{
		int camp = *(int*)((uint64_t)_this + 0x28);
		if (camp == 0){
			LOGI("player 0");
			value * dmgmul;
		}
		if (camp == 1){
			LOGI("enemy 1");
			value / defmul;
		}
	}
	return orig_ModifyHp(_this, value);
}

bool (*orig_UpdateSkill)(void *_this, float value);
bool UpdateSkill(void* _this, float value) {
	if(_this != NULL && hack1)
	{ 
		*(float *) ((uint64_t) _this + 0x20) = 0; // consumeMana
		*(float *) ((uint64_t) _this + 0x24) = 0; // skillCooldown
		*(float *) ((uint64_t) _this + 0x28) = 0; // CDTime
		//LOGD("ffff");
	}
	//LOGD("offf");
	return orig_UpdateSkill(_this, value);
}

void *hack_thread(void *) {
	
    // loop until our target library is found
    ProcMap il2cppMap;
    do {
		LOGD(libName);
        il2cppMap = KittyMemory::getLibraryMap(libName);
        sleep(1);
    } while (!il2cppMap.isValid());

	//ActorInfo
    MSHookFunction((void*)getAbsoluteAddress(libName, 0x1200388), (void*)ModifyHp, (void**) &orig_ModifyHp);
    MSHookFunction((void*)getAbsoluteAddress(libName, 0xA9E79C), (void*)UpdateSkill, (void**) &orig_UpdateSkill);
	
	/// MonsterAI
	// CanAttack
	my_cool_Patches.Patch1 = MemoryPatch::createWithHex(libName, 0x49086C, "00 00 A0 E3 1E FF 2F E1");
	
	// AttackOrAssault
	my_cool_Patches.Patch2 = MemoryPatch::createWithHex(libName, 0x4913D8, "00 00 A0 E3 1E FF 2F E1");
	
	// MoveOnPortal
	my_cool_Patches.Patch3 = MemoryPatch::createWithHex(libName, 0x48E5D0, "00 00 A0 E3 1E FF 2F E1");
	
	// MoveOnPath
	my_cool_Patches.Patch4 = MemoryPatch::createWithHex(libName, 0x48CDBC, "00 00 A0 E3 1E FF 2F E1");
	
	// BuildActorInfo
	my_cool_Patches.Patch5 = MemoryPatch::createWithHex(libName, 0x48B5C4, "1E FF 2F E1");
	LOGD("2");
    return NULL;
}

__attribute__((constructor))
void libhook_main() {
	pthread_t ptid;
	pthread_create(&ptid, NULL, hack_thread, NULL);
}
