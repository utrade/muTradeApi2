#include "bracketorderparams.h"
#include "ui_bracketordergui.h"

BracketOrderParams::BracketOrderParams(Ui::BracketOrderGui *ui)
{
    _transactionType  = new API2::PARAM("transactionType", "", NULL, API2::UI_ELEMENT_NO_UI, API2::DATA_TYPE_CHARACTER, API2::UI_STATE_DISABLED, API2::TABLE_STATE_HIDE, API2::DB_FEILD_SHOW);
    _clientId         = new API2::PARAM("clientId", "", NULL, API2::UI_ELEMENT_NO_UI , API2::DATA_TYPE_INTEGER ,  API2::UI_STATE_DISABLED , API2::TABLE_STATE_HIDE , API2::DB_FEILD_SHOW);
    _strategyId       = new API2::PARAM("strategyId","S_ID", NULL, API2::UI_ELEMENT_NO_UI, API2::DATA_TYPE_INTEGER, API2::UI_STATE_ENABLED, API2::TABLE_STATE_SHOW, API2::DB_FEILD_SHOW);
    _adminTokenId     = new API2::PARAM("adminTokenId","Token_Id", NULL, API2::UI_ELEMENT_NO_UI, API2::DATA_TYPE_UNSIGNED_LONG, API2::UI_STATE_DISABLED, API2::TABLE_STATE_SHOW, API2::DB_FEILD_SHOW);
    _state            = new API2::PARAM("state","STATE", NULL, API2::UI_ELEMENT_NO_UI , API2::DATA_TYPE_INTEGER ,  API2::UI_STATE_ENABLED , API2::TABLE_STATE_SHOW , API2::DB_FEILD_SHOW);
    _strategyComment  = new API2::PARAM("strategyComment","COMMENT", NULL, API2::UI_ELEMENT_NO_UI, API2::DATA_TYPE_STRING , API2::UI_STATE_DISABLED , API2::TABLE_STATE_SHOW , API2::DB_FEILD_SHOW);
    _riskStatus       = new API2::PARAM("riskStatus","",NULL,API2::UI_ELEMENT_NO_UI,API2::DATA_TYPE_SHORT,API2::UI_STATE_DISABLED,API2::TABLE_STATE_HIDE,API2::DB_FEILD_SHOW);
    _portfolioId      = new API2::PARAM("portfolioId","PORT_ID",NULL,API2::UI_ELEMENT_NO_UI,API2::DATA_TYPE_UNSIGNED_LONG,API2::UI_STATE_DISABLED,API2::TABLE_STATE_SHOW,API2::DB_FEILD_SHOW);
    _sequenceNumber   = new API2::PARAM("sequenceNumber","", NULL, API2::UI_ELEMENT_NO_UI, API2::DATA_TYPE_INTEGER, API2::UI_STATE_DISABLED , API2::TABLE_STATE_HIDE , API2::DB_FEILD_SHOW);
    _oldStrategyId    = new API2::PARAM("oldStrategyId","OLD_S_ID", NULL, API2::UI_ELEMENT_NO_UI, API2::DATA_TYPE_INTEGER, API2::UI_STATE_DISABLED, API2::TABLE_STATE_HIDE, API2::DB_FEILD_SHOW);
    _symbolId         = new API2::PARAM("symbolidFirstLeg" , "SID" , NULL , API2::UI_ELEMENT_NO_UI , API2::DATA_TYPE_UNSIGNED_LONG ,  API2::UI_STATE_DISABLED , API2::TABLE_STATE_SHOW , API2::DB_FEILD_SHOW);
    _symbolName       = new API2::PARAM("symbolName","SYMBOL", NULL, API2::UI_ELEMENT_NO_UI , API2::DATA_TYPE_STRING ,  API2::UI_STATE_DISABLED , API2::TABLE_STATE_SHOW , API2::DB_FEILD_HIDE);
    _mode             = new API2::PARAM("mode", "Order Mode", ui->orderComboBox, API2::UI_ELEMENT_COMBO_BOX , API2::DATA_TYPE_INTEGER , API2::UI_STATE_ENABLED , API2::TABLE_STATE_SHOW , API2::DB_FEILD_SHOW , API2::UPDATE_STATE_ENABLE);

    _orderTypeLeg1    = new API2::PARAM("orderTypeLeg1","Order Type Leg1",ui->orderLeg1ComboBox,API2::UI_ELEMENT_COMBO_BOX, API2::DATA_TYPE_INTEGER, API2::UI_STATE_ENABLED,API2::TABLE_STATE_SHOW, API2::DB_FEILD_SHOW, API2::UPDATE_STATE_ENABLE);
    _fillTypeLeg1     = new API2::PARAM("fillTypeLeg1","Fill Type Leg1",ui->fillLeg1ComboBox,API2::UI_ELEMENT_COMBO_BOX,API2::DATA_TYPE_INTEGER, API2::UI_STATE_ENABLED,API2::TABLE_STATE_SHOW,API2::DB_FEILD_SHOW,API2::UPDATE_STATE_ENABLE);
    _quantityLeg1     = new API2::PARAM("quantityLeg1","Quantity Leg1",ui->quantityLeg1SpinBox,API2::UI_ELEMENT_SPIN_BOX,API2::DATA_TYPE_INTEGER,API2::UI_STATE_ENABLED,API2::TABLE_STATE_SHOW,API2::DB_FEILD_SHOW,API2::UPDATE_STATE_ENABLE);
    _limitPriceLeg1   = new API2::PARAM("limitPriceLeg1","Limit Price Leg1",ui->limitLeg1DoubleSpinBox,API2::UI_ELEMENT_DOUBLE_SPIN_BOX,API2::DATA_TYPE_DOUBLE,API2::UI_STATE_ENABLED,API2::TABLE_STATE_SHOW,API2::DB_FEILD_SHOW,API2::UPDATE_STATE_ENABLE);
    _triggerPriceLeg1 = new API2::PARAM("triggerPriceLeg1","Trigger Price Leg1",ui->triggerLeg1DoubleSpinBox,API2::UI_ELEMENT_DOUBLE_SPIN_BOX,API2::DATA_TYPE_DOUBLE,API2::UI_STATE_ENABLED,API2::TABLE_STATE_SHOW,API2::DB_FEILD_SHOW,API2::UPDATE_STATE_ENABLE);
    _orderTypeLeg2    = new API2::PARAM("orderTypeLeg2","Order Type Leg2",ui->orderLeg2ComboBox,API2::UI_ELEMENT_COMBO_BOX, API2::DATA_TYPE_INTEGER, API2::UI_STATE_ENABLED,API2::TABLE_STATE_SHOW, API2::DB_FEILD_SHOW, API2::UPDATE_STATE_ENABLE);
    _fillTypeLeg2     = new API2::PARAM("fillTypeLeg2","Fill Type Leg2",ui->fillLeg2ComboBox,API2::UI_ELEMENT_COMBO_BOX,API2::DATA_TYPE_INTEGER, API2::UI_STATE_ENABLED,API2::TABLE_STATE_SHOW,API2::DB_FEILD_SHOW,API2::UPDATE_STATE_ENABLE);
    _quantityLeg2     = new API2::PARAM("quantityLeg2","Quantity Leg2",ui->quantityLeg2ComboBox,API2::UI_ELEMENT_COMBO_BOX,API2::DATA_TYPE_INTEGER,API2::UI_STATE_ENABLED,API2::TABLE_STATE_SHOW,API2::DB_FEILD_SHOW,API2::UPDATE_STATE_ENABLE);
    _limitPriceLeg2   = new API2::PARAM("limitPriceLeg2","Limit Price Leg2",ui->limitLeg2DoubleSpinBox,API2::UI_ELEMENT_DOUBLE_SPIN_BOX,API2::DATA_TYPE_DOUBLE,API2::UI_STATE_ENABLED,API2::TABLE_STATE_SHOW,API2::DB_FEILD_SHOW,API2::UPDATE_STATE_ENABLE);
    _triggerPriceLeg2 = new API2::PARAM("triggerPriceLeg2","Trigger Price Leg2",ui->triggerLeg2DoubleSpinBox,API2::UI_ELEMENT_DOUBLE_SPIN_BOX,API2::DATA_TYPE_DOUBLE,API2::UI_STATE_ENABLED,API2::TABLE_STATE_SHOW,API2::DB_FEILD_SHOW,API2::UPDATE_STATE_ENABLE);
    _orderTypeLeg3    = new API2::PARAM("orderTypeLeg3","Order Type Leg3",ui->orderLeg3ComboBox,API2::UI_ELEMENT_COMBO_BOX, API2::DATA_TYPE_INTEGER, API2::UI_STATE_ENABLED,API2::TABLE_STATE_SHOW, API2::DB_FEILD_SHOW, API2::UPDATE_STATE_ENABLE);
    _fillTypeLeg3     = new API2::PARAM("fillTypeLeg3","Fill Type Leg3",ui->fillLeg3ComboBox,API2::UI_ELEMENT_COMBO_BOX,API2::DATA_TYPE_INTEGER, API2::UI_STATE_ENABLED,API2::TABLE_STATE_SHOW,API2::DB_FEILD_SHOW,API2::UPDATE_STATE_ENABLE);
    _quantityLeg3     = new API2::PARAM("quantityLeg3","Quantity Leg3",ui->quantityLeg3ComboBox,API2::UI_ELEMENT_COMBO_BOX,API2::DATA_TYPE_INTEGER,API2::UI_STATE_ENABLED,API2::TABLE_STATE_SHOW,API2::DB_FEILD_SHOW,API2::UPDATE_STATE_ENABLE);
    _limitPriceLeg3   = new API2::PARAM("limitPriceLeg3","Limit Price Leg3",ui->limitLeg3DoubleSpinBox,API2::UI_ELEMENT_DOUBLE_SPIN_BOX,API2::DATA_TYPE_DOUBLE,API2::UI_STATE_ENABLED,API2::TABLE_STATE_SHOW,API2::DB_FEILD_SHOW,API2::UPDATE_STATE_ENABLE);
    _triggerPriceLeg3 = new API2::PARAM("triggerPriceLeg3","Trigger Price Leg3",ui->triggerLeg3DoubleSpinBox,API2::UI_ELEMENT_DOUBLE_SPIN_BOX,API2::DATA_TYPE_DOUBLE,API2::UI_STATE_ENABLED,API2::TABLE_STATE_SHOW,API2::DB_FEILD_SHOW,API2::UPDATE_STATE_ENABLE);
    makeParamsList();
}

void BracketOrderParams::addParams(API2::PARAM *param, int columnIndex, short filterWidget,bool isEditable)
{
    _paramsMap.insert(param->getParamName(),param);
    param->setColumnIndex(columnIndex);
    param->setFilterType(filterWidget);
    param->setColumnEditable(isEditable);
}

void BracketOrderParams::makeParamsList()
{
    short index=1;
    addParams(_transactionType);
    addParams(_clientId);
    addParams(_riskStatus);
    addParams(_sequenceNumber);
    addParams(_oldStrategyId);
    addParams(_adminTokenId, index++);
    addParams(_strategyId,index++,API2::WidgetType_LINEEDIT);
    addParams(_state,index++);
    addParams(_symbolId,index++);
    addParams(_symbolName,index++);
    _adminTokenId->setColumnHidden(true);
    _symbolId->setColumnHidden(true);
    addParams(_portfolioId,index++);
    addParams(_strategyComment,index++);
    addParams(_mode, index++, API2::WidgetType_COMBOBOX);

    addParams(_orderTypeLeg1,index++,API2::WidgetType_COMBOBOX);
    addParams(_fillTypeLeg1,index++,API2::WidgetType_COMBOBOX);
    addParams(_quantityLeg1,index++,API2::WidgetType_MAX,true);
    addParams(_limitPriceLeg1,index++,API2::WidgetType_MAX,true);
    addParams(_triggerPriceLeg1,index++,API2::WidgetType_MAX,true);
    addParams(_orderTypeLeg2,index++,API2::WidgetType_COMBOBOX);
    addParams(_fillTypeLeg2,index++,API2::WidgetType_COMBOBOX);
    addParams(_quantityLeg2,index++);
    addParams(_limitPriceLeg2,index++,API2::WidgetType_MAX,true);
    addParams(_triggerPriceLeg2,index++,API2::WidgetType_MAX,true);
    addParams(_orderTypeLeg3,index++,API2::WidgetType_COMBOBOX);
    addParams(_fillTypeLeg3,index++,API2::WidgetType_COMBOBOX);
    addParams(_quantityLeg3,index++);
    addParams(_limitPriceLeg3,index++,API2::WidgetType_MAX,true);
    addParams(_triggerPriceLeg3,index++,API2::WidgetType_MAX,true);
}
