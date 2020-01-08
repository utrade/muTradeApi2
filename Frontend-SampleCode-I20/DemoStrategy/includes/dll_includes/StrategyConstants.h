#ifndef STRATEGYCONSTANTS_H
#define STRATEGYCONSTANTS_H
#include "qstring.h"
namespace STRATEGY_CONST
{
static const QString IOC_STR ="IOC";
static const QString BID_STR ="BID";
static const QString FIRST_LEG ="1L";
static const QString SECOND_LEG ="2L";
static const QString THIRD_LEG ="3L";
static const QString FOURTH_LEG ="4L";

static const QString FUT_REF_PRICE = "deltaFutPrice";
static const QString OPTION_PRICE = "deltaSpread";
static const QString DELTA_PERCENTAGE = "deltaPercentage";
static const QString STRATEGY_TYPE = "StrategyType";
static const QString INTERST = "interstRate";

static const QString RUN_STATE="RUN";
static const QString READY_STATE="READY";
static const QString ADMIN_TOKEN_ID = "adminTokenId";
static const QString HIT_SPREAD = "hitSpread";
static const QString TRY_SPREAD = "trySpread";

static const QString SPREAD_DIFF = "spdDiff";
static const QString MIN_SPREAD = "minProfit";
static const QString STRATEGY_ID = "strategyId";
static const QString checkSpread = "checkSpread";
static const QString SYMBOL_ID_FIRST_LEG = "symbolidFirstLeg";
static const QString SYMBOL_ID_SECOND_LEG = "symbolidSecondLeg";
static const QString SYMBOL_ID_THIRD_LEG = "symbolidThirdLeg";
static const QString SYMBOL_ID_FOURTH_LEG = "symbolidFourthLeg";
static const QString STATE = "state";
static const QString STRATEGY_COMMENT = "strategyComment";
static const QString PORTFOLIO_ID = "portfolioId";
static const QString STRATEGY_SIDE ="strategySide";
static const QString SEQUENCE_NUMBER = "sequenceNumber";
static const QString RISK_STATUS = "riskStatus";
static const QString PORTFOLIO_NAME = "portfolioName";
static const QString PORTFOLIO_SPREAD = "portfolioSpread";
static const QString SID_LEG1 = "SIDTotalQtyLeg1";
static const QString ALL = "ALL";
static const QString AWAITED = "AWAITED";
static const QString NA_STR = "-N/A-";
static const QString UNKNOWNSTR =  "Unknown";
static const QString ORDER_TYPE = "Order type";
static const QString SPREAD_TYPE = "Spread type";
static const QString GRAB_OPP = "Grab Opp";
static const QString BIDDING_LEG = "Bidding leg";
static const QString MODIFY = "Modify";
static const QString SPOT = "Spot";

static const QString BLACK = "#000000";
static const QString WHITE = "#FFFFFF";
static const QString GREY  = "#808080";
static const QString YELLOW = "#FFFF00";
static const QString RED = "#FF0000";
static const QString GREEN = "#008000";
static const QString LRED = "#CC0066";
static const QString ORANGE = "#FF7F50";
static const QString AQUAMARINE = "#7FFFD4";
static const QString PURPLE = "#800080";

}
#endif // STRATEGYCONSTANTS_H
