#include "header.h"

extern EWRAM_DATA struct Struct203CEC4 *gUnknown_0203CEC4;
EWRAM_DATA struct Struct203CEC8 gUnknown_0203CEC8 = {0};
extern void CursorCb_FieldMove(u8 taskId);
extern u8 gMoveNames[MOVES_COUNT][MOVE_NAME_LENGTH + 1];
extern void task_brm_cancel_1_on_keypad_a_or_b(u8 taskId);
extern void CB2_ReturnToField(void);

enum
{
    MENU_SUMMARY,
    MENU_SWITCH,
    MENU_CANCEL1,
    MENU_ITEM,
    MENU_GIVE,
    MENU_TAKE_ITEM,
    MENU_MAIL,
    MENU_TAKE_MAIL,
    MENU_READ,
    MENU_CANCEL2,
    MENU_SHIFT,
    MENU_SEND_OUT,
    MENU_ENTER,
    MENU_NO_ENTRY,
    MENU_STORE,
    MENU_REGISTER,
    MENU_TRADE1,
    MENU_TRADE2,
    MENU_TOSS,
    MENU_FIELD_MOVES,
};

enum
{
    FIELD_MOVE_CUT,
    FIELD_MOVE_FLASH,
    FIELD_MOVE_ROCK_SMASH,
    FIELD_MOVE_STRENGTH,
    FIELD_MOVE_SURF,
    FIELD_MOVE_FLY,
    FIELD_MOVE_DIVE,
    FIELD_MOVE_WATERFALL,
    FIELD_MOVE_TELEPORT,
    FIELD_MOVE_DIG,
    FIELD_MOVE_SECRET_POWER,
    FIELD_MOVE_MILK_DRINK,
    FIELD_MOVE_SOFT_BOILED,
    FIELD_MOVE_SWEET_SCENT,
	FIELD_MOVE_RECOVER,
};

#define FIELD_MOVE_TERMINATOR 14   //0xE

extern const u8 gText_Summary5[];
extern const u8 gText_Switch2[];
extern const u8 gText_Cancel2[];
extern const u8 gText_Item[];
extern const u8 gMenuText_Give[];
extern const u8 gText_Take[];
extern const u8 gText_Mail[];
extern const u8 gText_Take2[];
extern const u8 gText_Read2[];
extern const u8 gText_Shift[];
extern const u8 gText_SendOut[];
extern const u8 gText_Enter[];
extern const u8 gText_NoEntry[];
extern const u8 gText_Store[];
extern const u8 gText_Register[];
extern const u8 gText_Trade4[];
extern const u8 gMenuText_Toss[];

extern void CursorCb_Summary(u8 taskId);
extern void CursorCb_Switch(u8 taskId);
extern void CursorCb_Cancel1(u8 taskId);
extern void CursorCb_Item(u8 taskId);
extern void CursorCb_Give(u8 taskId);
extern void CursorCb_TakeItem(u8 taskId);
extern void CursorCb_Mail(u8 taskId);
extern void CursorCb_TakeMail(u8 taskId);
extern void CursorCb_Read(u8 taskId);
extern void CursorCb_Cancel2(u8 taskId);
extern void CursorCb_SendMon(u8 taskId);
extern void CursorCb_Enter(u8 taskId);
extern void CursorCb_NoEntry(u8 taskId);
extern void CursorCb_Store(u8 taskId);
extern void CursorCb_Register(u8 taskId);
extern void CursorCb_Trade1(u8 taskId);
extern void CursorCb_Trade2(u8 taskId);
extern void CursorCb_Toss(u8 taskId);
extern void CursorCb_FieldMove(u8 taskId);

extern bool8 SetUpFieldMove_Cut(void);
extern bool8 SetUpFieldMove_Flash(void);
extern bool8 SetUpFieldMove_RockSmash(void);
extern bool8 SetUpFieldMove_Strength(void);
extern bool8 SetUpFieldMove_Surf(void);
extern bool8 SetUpFieldMove_Fly(void);
extern bool8 SetUpFieldMove_Dive(void);
extern bool8 SetUpFieldMove_Waterfall(void);
extern bool8 SetUpFieldMove_Teleport(void);
extern bool8 SetUpFieldMove_Dig(void);
extern bool8 SetUpFieldMove_SecretPower(void);
extern bool8 SetUpFieldMove_SoftBoiled(void);
extern bool8 SetUpFieldMove_SweetScent(void);

static void FieldMove_Effect(u8 taskId);

struct
{
    const u8 *text;
    TaskFunc func;
} const sCursorOptions[] =
{
    [MENU_SUMMARY] = {gText_Summary5, CursorCb_Summary},
    [MENU_SWITCH] = {gText_Switch2, CursorCb_Switch},
    [MENU_CANCEL1] = {gText_Cancel2, CursorCb_Cancel1},
    [MENU_ITEM] = {gText_Item, CursorCb_Item},
    [MENU_GIVE] = {gMenuText_Give, CursorCb_Give},
    [MENU_TAKE_ITEM] = {gText_Take, CursorCb_TakeItem},
    [MENU_MAIL] = {gText_Mail, CursorCb_Mail},
    [MENU_TAKE_MAIL] = {gText_Take2, CursorCb_TakeMail},
    [MENU_READ] = {gText_Read2, CursorCb_Read},
    [MENU_CANCEL2] = {gText_Cancel2, CursorCb_Cancel2},
    [MENU_SHIFT] = {gText_Shift, CursorCb_SendMon},
    [MENU_SEND_OUT] = {gText_SendOut, CursorCb_SendMon},
    [MENU_ENTER] = {gText_Enter, CursorCb_Enter},
    [MENU_NO_ENTRY] = {gText_NoEntry, CursorCb_NoEntry},
    [MENU_STORE] = {gText_Store, CursorCb_Store},
    [MENU_REGISTER] = {gText_Register, CursorCb_Register},
    [MENU_TRADE1] = {gText_Trade4, CursorCb_Trade1},
    [MENU_TRADE2] = {gText_Trade4, CursorCb_Trade2},
    [MENU_TOSS] = {gMenuText_Toss, CursorCb_Toss},
    [MENU_FIELD_MOVES + FIELD_MOVE_CUT] = {gMoveNames[MOVE_CUT], CursorCb_FieldMove},
    [MENU_FIELD_MOVES + FIELD_MOVE_FLASH] = {gMoveNames[MOVE_FLASH], CursorCb_FieldMove},
    [MENU_FIELD_MOVES + FIELD_MOVE_ROCK_SMASH] = {gMoveNames[MOVE_ROCK_SMASH], CursorCb_FieldMove},
    [MENU_FIELD_MOVES + FIELD_MOVE_STRENGTH] = {gMoveNames[MOVE_STRENGTH], CursorCb_FieldMove},
    [MENU_FIELD_MOVES + FIELD_MOVE_SURF] = {gMoveNames[MOVE_SURF], CursorCb_FieldMove},
    [MENU_FIELD_MOVES + FIELD_MOVE_FLY] = {gMoveNames[MOVE_FLY], CursorCb_FieldMove},
    [MENU_FIELD_MOVES + FIELD_MOVE_DIVE] = {gMoveNames[MOVE_DIVE], CursorCb_FieldMove},
    [MENU_FIELD_MOVES + FIELD_MOVE_WATERFALL] = {gMoveNames[MOVE_WATERFALL], CursorCb_FieldMove},
    [MENU_FIELD_MOVES + FIELD_MOVE_TELEPORT] = {gMoveNames[MOVE_TELEPORT], CursorCb_FieldMove},
    [MENU_FIELD_MOVES + FIELD_MOVE_DIG] = {gMoveNames[MOVE_DIG], CursorCb_FieldMove},
    [MENU_FIELD_MOVES + FIELD_MOVE_SECRET_POWER] = {gMoveNames[MOVE_SECRET_POWER], CursorCb_FieldMove},
    [MENU_FIELD_MOVES + FIELD_MOVE_MILK_DRINK] = {gMoveNames[MOVE_MILK_DRINK], CursorCb_FieldMove},
    [MENU_FIELD_MOVES + FIELD_MOVE_SOFT_BOILED] = {gMoveNames[MOVE_SOFTBOILED], CursorCb_FieldMove},
    [MENU_FIELD_MOVES + FIELD_MOVE_SWEET_SCENT] = {gMoveNames[MOVE_SWEET_SCENT], CursorCb_FieldMove},
    [MENU_FIELD_MOVES + FIELD_MOVE_RECOVER] = {gMoveNames[MOVE_RECOVER], FieldMove_Effect},
};

const u16 sFieldMoves[] =
{
    MOVE_CUT, MOVE_FLASH, MOVE_ROCK_SMASH, MOVE_STRENGTH, MOVE_SURF, MOVE_FLY, MOVE_DIVE, MOVE_WATERFALL, MOVE_TELEPORT,
    MOVE_DIG, MOVE_SECRET_POWER, MOVE_MILK_DRINK, MOVE_SOFTBOILED, MOVE_SWEET_SCENT, MOVE_RECOVER, FIELD_MOVE_TERMINATOR
};

struct
{
    bool8 (*fieldMoveFunc)(void);
    u8 msgId;
} const sFieldMoveCursorCallbacks[] =
{
    [FIELD_MOVE_CUT] = {SetUpFieldMove_Cut, 0x07},
    [FIELD_MOVE_FLASH] = {SetUpFieldMove_Flash, 0x0d},
    [FIELD_MOVE_ROCK_SMASH] = {SetUpFieldMove_RockSmash, 0x0d},
    [FIELD_MOVE_STRENGTH] = {SetUpFieldMove_Strength, 0x0d},
    [FIELD_MOVE_SURF] = {SetUpFieldMove_Surf, 0x08},
    [FIELD_MOVE_FLY] = {SetUpFieldMove_Fly, 0x0d},
    [FIELD_MOVE_DIVE] = {SetUpFieldMove_Dive, 0x0d},
    [FIELD_MOVE_WATERFALL] = {SetUpFieldMove_Waterfall, 0x0d},
    [FIELD_MOVE_TELEPORT] = {SetUpFieldMove_Teleport, 0x0d},
    [FIELD_MOVE_DIG] = {SetUpFieldMove_Dig, 0x0d},
    [FIELD_MOVE_SECRET_POWER] = {SetUpFieldMove_SecretPower, 0x0d},
    [FIELD_MOVE_MILK_DRINK] = {SetUpFieldMove_SoftBoiled, 0x10},
    [FIELD_MOVE_SOFT_BOILED] = {SetUpFieldMove_SoftBoiled, 0x10},
    [FIELD_MOVE_SWEET_SCENT] = {SetUpFieldMove_SweetScent, 0x0d},
    [FIELD_MOVE_RECOVER] = {SetUpFieldMove_SoftBoiled, 0x0d},
};

/*其中有一部分无效果，因此未实装
void CreateActionList(struct pokemon *mons, u8 slotId)
{
    u8 i, j;

    gUnknown_0203CEC4->listSize = 0;
    AppendToList(gUnknown_0203CEC4->actions, &gUnknown_0203CEC4->listSize, MENU_SUMMARY);
	
	//不知为何，这段无效果
    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        for (j = 0; sFieldMoves[j] != FIELD_MOVE_TERMINATOR; j++)
        {
            if (get_attributes(&mons[slotId], i + MON_DATA_MOVE1, 0) == sFieldMoves[j])
            {
                AppendToList(gUnknown_0203CEC4->actions, &gUnknown_0203CEC4->listSize, j + MENU_FIELD_MOVES);
                break;
            }
        }
    }
	//
	
    if (!InBattlePike())
    {
        if (get_attributes(&mons[1], MON_DATA_SPECIES, 0) != SPECIES_NONE)
            AppendToList(gUnknown_0203CEC4->actions, &gUnknown_0203CEC4->listSize, MENU_SWITCH);
        if (ItemIsMail(get_attributes(&mons[slotId], MON_DATA_HELD_ITEM, 0)))
            AppendToList(gUnknown_0203CEC4->actions, &gUnknown_0203CEC4->listSize, MENU_MAIL);
        else
            AppendToList(gUnknown_0203CEC4->actions, &gUnknown_0203CEC4->listSize, MENU_ITEM);
    }
    AppendToList(gUnknown_0203CEC4->actions, &gUnknown_0203CEC4->listSize, MENU_CANCEL1);
}
*/

static void FieldMove_Effect(u8 taskId)
{
    u8 fieldMove = gUnknown_0203CEC4->actions[Menu_GetCursorPos()] - MENU_FIELD_MOVES;

    PlaySE(SE_SELECT);
    if (sFieldMoveCursorCallbacks[fieldMove].fieldMoveFunc == NULL)
        return;
	
	sub_81B302C(&gUnknown_0203CEC4->windowId[0]);
    sub_81B302C(&gUnknown_0203CEC4->windowId[1]);
	
	 if (sub_81221AC() == TRUE || InUnionRoom() == TRUE)
    {
		display_pokemon_menu_message(sFieldMoveCursorCallbacks[fieldMove].msgId);
		tasks[taskId].function = task_brm_cancel_1_on_keypad_a_or_b;
	}
	else if (sFieldMoveCursorCallbacks[fieldMove].fieldMoveFunc() == TRUE){
		
		switch (fieldMove)
            {
				case FIELD_MOVE_RECOVER:
					sub_8161560(taskId);
					break;
				default:
					gUnknown_0203CEC8.exitCallback = CB2_ReturnToField;
					sub_81B12C0(taskId);
					break;
			}
	}
}
