#ifndef SHAREDENUMS_H
#define SHAREDENUMS_H
#ifndef MUTRADE_CLIENT
#include "../../includes/api_includes/sharedDefines.h"
#include "dllDefines.h"
#else
#include "../../api2/headers/sharedDefines.h"
#include "qtversiondefines.h"
#endif
namespace API2
{

namespace DllCMD
{
enum OrderMode
{
    OrderMode_BUY = 0,
    OrderMode_SELL,
    OrderMode_BOTH,
    OrderMode_MAX
};

enum StrategyExecType
{
    StrategyExecType_BID=0,
    StrategyExecType_IOC=1,
    StrategyExecType_MUL_IOC=2,
    StrategyExecType_MAX=3
};

enum TwoLegArbitrageHedgeMethod
{
    TwoLegArbitrageHedgeMethod_IOC=0,
    TwoLegArbitrageHedgeMethod_BEST_BID_ASK=1,
    TwoLegArbitrageHedgeMethod_ASK_BID=2,
    TwoLegArbitrageHedgeMethod_ACTUAL_DIFF=3,
    TwoLegArbitrageHedgeMethod_ACTUAL_DIFF_IOC_BEST=4,
    TwoLegArbitrageHedgeMethod_ACTUAL_DIFF_LIMIT_BEST=5,
    TwoLegArbitrageHedgeMethod_ACTUAL_DIFF_IOC_BEST_SQUARE_OFF=6,
    TwoLegArbitrageHedgeMethod_ACTUAL_DIFF_LIMIT_BEST_SQUARE_OFF=7,
    TwoLegArbitrageHedgeMethod_HIT_BID_ASK=8,
    TwoLegArbitrageHedgeMethod_DEFAULT=9,
    TwoLegArbitrageHedgeMethod_MAX=10
};

enum OptionMode
{
    OptionMode_PUT,
    OptionMode_CALL,
    OptionMode_MAX
};

enum TwoLegThreeLegSpreadType
{
    TwoLegThreeLegSpreadType_PRODUCT_DIFF,
    TwoLegThreeLegSpreadType_ACTUAL_DIFF,
    TwoLegThreeLegSpreadType_BASE_DIFF,
    TwoLegThreeLegSpreadType_BPS_SPREAD,
    TwoLegThreeLegSpreadType_MAX
};

enum OrderType {
    OrderType_LIMIT,
    OrderType_MARKET,
    OrderType_STOP_LIMIT,
    OrderType_STOP,
    OrderType_BestPrice,
    OrderType_Ask1,
    OrderType_Bid1,
    OrderType_Ask1P1,
    OrderType_Ask1P2,
    OrderType_Ask1P3,
    OrderType_Bid1P1,
    OrderType_Bid1P2,
    OrderType_Bid1P3,
    OrderType_MAX
};

enum AccountType
{
    AccountType_DEALER,
    AccountType_PRO,
    AccountType_SPLCLIENT,
    AccountType_INST,
    AccountType_MAX
};

}


///////////////////////End of Command namespace


/*Basic Startegy Element Enum*/
enum UI_ELEMENT
{
    UI_ELEMENT_LABEL=0,
    UI_ELEMENT_COMBO_BOX=1,
    UI_ELEMENT_LINE_EDIT=2,
    UI_ELEMENT_SPIN_BOX=3,
    UI_ELEMENT_DOUBLE_SPIN_BOX=4,
    UI_ELEMENT_CHECK_BOX=5,
    UI_ELEMENT_PUSH_BUTTON=6,
    UI_ELEMENT_RADIO_BUTTON=7,
    UI_ELEMENT_DATE_TIME=8,
    UI_ELEMENT_NO_UI=9,
    UI_ELEMENT_SLIDER=10,
    UI_ELEMENT_GROUP_BOX=11,
    UI_ELEMENT_TIME_EDIT=12,
    UI_ELEMENT_RADIO_BUTTON_GROUP=13,
    UI_ELEMENT_TIME_EDIT_SECONDS = 14,
    UI_ELEMENT_SPIN_BOX_NON_QTY = 15,
    UI_ELEMENT_MAX=16
};

enum UI_STATE
{
    UI_STATE_DISABLED=0,
    UI_STATE_ENABLED=1,
    UI_STATE_MAX=2
};

enum TABLE_STATE
{
    TABLE_STATE_HIDE=0,
    TABLE_STATE_SHOW=1,
    TABLE_STATE_MAX=2
};

enum DB_FEILD
{
    DB_FEILD_HIDE=0,
    DB_FEILD_SHOW=1,
    DB_FEILD_MAX=2
};

enum DATA_TYPE
{
    DATA_TYPE_SHORT=0,
    DATA_TYPE_INTEGER=1,
    DATA_TYPE_FLOAT=2,
    DATA_TYPE_DOUBLE=3,
    DATA_TYPE_STRING=4,
    DATA_TYPE_SIGNED_LONG=5,
    DATA_TYPE_UNSIGNED_LONG=6,
    DATA_TYPE_CHARACTER=7,
    DATA_TYPE_BOOLEAN=8,
    DATA_TYPE_MAX=9
};

enum UPDATE_STATE
{
    UPDATE_STATE_DISABLE=0,
    UPDATE_STATE_ENABLE=1,
    UPDATE_STATE_MAX=2
};

enum SHOW_IN_PORTFOLIO
{
    SHOW_IN_PORTFOLIO_DISABLE=0,
    SHOW_IN_PORTFOLIO_ENABLE=1,
    SHOW_IN_PORTFOLIO_MAX=2
};


/**
  *@brief Enum Controll Button Panel
  */
enum CTRL_BTN
{
    CTRL_BTN_NEW = 0,
    CTRL_BTN_EDIT = 1,
    CTRL_BTN_COMMIT = 2,
    CTRL_BTN_ADD = 3,
    CTRL_BTN_REMOVE = 4,
    CTRL_BTN_RUN = 5,
    CTRL_BTN_STOP = 6,
    CTRL_BTN_STOPALL = 7,
    CTRL_BTN_SETTINGS = 8,
    CTRL_BTN_MINIMIZE = 9,
    CTRL_CHECKBOX_SHOWHIDE = 10,
    CTRL_BTN_MAX
};

/**
  *@brief Enum UI_STATE
  */
enum PORTFOLIO_STATE
{
    PORTFOLIO_STATE_INITIALISED=0,
    PORTFOLIO_STATE_New_Clicked=1,
    PORTFOLIO_STATE_OneCheckedRunning=2,
    PORTFOLIO_STATE_OneCheckedReady=3,
    PORTFOLIO_STATE_MultiCheckedRunning=4,
    PORTFOLIO_STATE_MultiCheckedReady=5,
    PORTFOLIO_STATE_MultiCheckedAll=6,
    PORTFOLIO_STATE_EditClickedRunning=7,
    PORTFOLIO_STATE_EditClickedReady=8,
    PORTFOLIO_STATE_AddClicked=9,
    PORTFOLIO_STATE_CommitClicked=10,
    PORTFOLIO_STATE_REMOVE_Clicked=11,
    PORTFOLIO_STATE_Terminate_clicked=12,
    PORTFOLIO_STATE_NEW_clicked_Old_Data=13,
    PORTFOLIO_STATE_MAX=14
};

/**
 *@brief ThreeLegArbitrage Enums
 */

enum LEGS
{
    FIRST_LEG = 0,
    SECOND_LEG = 1,
    THIRD_LEG = 2,
    FOURTH_LEG = 3,
    LEG_MAX = 4
};



/**
  *@brief Common TableView Enums
  */

enum Delegates
{
    Delegates_COMBOBOX,
    Delegates_LINEEDIT,
    Delegates_SPINBOX,
    Delegates_DSPINBOX,
    Delegates_CHECKBOX,
    Delegates_SPINBOX_NQ,
    Delegates_Max
};

/**
  *@WidgetType
  */
enum WidgetType
{
    WidgetType_LINEEDIT,
    WidgetType_COMBOBOX,
    WidgetType_DATETIME_FROM_TO,
    WidgetType_MAX
};

/**
  *@ ENUM SORTING_TYPE
  */
enum SortingType
{
    SortingType_Int,
    SortingType_UInt,
    SortingType_LongLong,
    SortingType_ULongLong,
    SortingType_Double,
    SortingType_Char,
    SortingType_Date,
    SortingType_Time,
    SortingType_DateTime,
    SortingType_String,
    SortingType_MAX
};

/**
  *@ ENUM SYM_PANEL ELEMENTS
  */
enum SYM_PANEL
{
    SYM_PANEL_ORD_MODE = 2,
    SYM_PANEL_SOURCE = 4,
    SYM_PANEL_EXCHANGE = 8,
    SYM_PANEL_INST = 16 ,
    SYM_PANEL_SYMBOL = 32,
    SYM_PANEL_EXPIRY = 64 ,
    SYM_PANEL_OP_MODE = 128,
    SYM_PANEL_STRIKE = 256,
    SYM_PANEL_MAX = 512
};

/**
  *@enum   CONT_HEDGING_MODE
  *@brief  Continues Hedging order mode
  */
enum CONT_HEDGING_MODE
{
    CONT_HEDGING_MODE_SAME_SIDE = 0,
    CONT_HEDGING_MODE_BOTH_SIDE = 1,
    CONT_HEDGING_MODE_MAX= 2
};

enum  INSRTUMENT_TYPE
{
    STOCK = 2,
    FUTURE =4,
    OPTION =8,
    SPREAD = 16
};
}
#endif // SHAREDENUMS_H
