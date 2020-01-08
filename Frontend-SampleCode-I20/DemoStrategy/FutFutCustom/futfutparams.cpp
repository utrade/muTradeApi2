#include "futfutparams.h"
#include "ui_uilibrary.h"

FutFutParams :: FutFutParams(Ui::UiLibrary *ui)
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

    _symbolId         = new API2::PARAM("symbolidFirstLeg" , "SID FL" , NULL , API2::UI_ELEMENT_NO_UI , API2::DATA_TYPE_UNSIGNED_LONG ,  API2::UI_STATE_DISABLED , API2::TABLE_STATE_SHOW , API2::DB_FEILD_SHOW);
    _symbolName       = new API2::PARAM("symbolName","SYMBOL FL", NULL, API2::UI_ELEMENT_NO_UI , API2::DATA_TYPE_STRING ,  API2::UI_STATE_DISABLED , API2::TABLE_STATE_SHOW , API2::DB_FEILD_HIDE);
    _mode             = new API2::PARAM("mode", "ORDER MODE FL", ui->comboBoxMode, API2::UI_ELEMENT_COMBO_BOX , API2::DATA_TYPE_INTEGER , API2::UI_STATE_ENABLED , API2::TABLE_STATE_SHOW , API2::DB_FEILD_SHOW , API2::UPDATE_STATE_ENABLE);
    _symbolId2        = new API2::PARAM("symbolidSecondLeg" , "SID SL" , NULL , API2::UI_ELEMENT_NO_UI , API2::DATA_TYPE_UNSIGNED_LONG ,  API2::UI_STATE_DISABLED , API2::TABLE_STATE_SHOW , API2::DB_FEILD_SHOW);
    _symbolName2      = new API2::PARAM("symbolName2","SYMBOL SL", NULL, API2::UI_ELEMENT_NO_UI , API2::DATA_TYPE_STRING ,  API2::UI_STATE_DISABLED , API2::TABLE_STATE_SHOW , API2::DB_FEILD_HIDE);
    _mode2            = new API2::PARAM("mode2", "ORDER MODE SL", ui->comboBoxMode2, API2::UI_ELEMENT_COMBO_BOX , API2::DATA_TYPE_INTEGER , API2::UI_STATE_ENABLED , API2::TABLE_STATE_SHOW , API2::DB_FEILD_SHOW , API2::UPDATE_STATE_ENABLE);
    _totalLots        = new API2::PARAM("totalLots", "TOTALLOTS", ui->spinBoxTotalLots,API2:: UI_ELEMENT_SPIN_BOX, API2::DATA_TYPE_INTEGER, API2::UI_STATE_ENABLED, API2::TABLE_STATE_SHOW, API2::DB_FEILD_SHOW , API2::UPDATE_STATE_ENABLE);
    _orderLots        = new API2::PARAM("orderLots", "ORDERLOTS", ui->spinBoxOrderLots,API2:: UI_ELEMENT_SPIN_BOX, API2::DATA_TYPE_INTEGER, API2::UI_STATE_ENABLED, API2::TABLE_STATE_SHOW, API2::DB_FEILD_SHOW , API2::UPDATE_STATE_ENABLE);
    _desiredSpread    = new API2::PARAM("desiredSpread", "SPREAD", ui->doubleSpinBoxDesiredSpread,API2:: UI_ELEMENT_DOUBLE_SPIN_BOX, API2::DATA_TYPE_DOUBLE, API2::UI_STATE_ENABLED, API2::TABLE_STATE_SHOW, API2::DB_FEILD_SHOW , API2::UPDATE_STATE_ENABLE);
    _hedgeMethod      = new API2::PARAM("hedgeMethod", "HEDGE METHOD", ui->comboBoxHedgeMethod, API2::UI_ELEMENT_COMBO_BOX , API2::DATA_TYPE_STRING ,  API2::UI_STATE_ENABLED , API2::TABLE_STATE_SHOW , API2::DB_FEILD_SHOW , API2::UPDATE_STATE_ENABLE);
    _marketPercentage = new API2::PARAM("mktPercentage", "MKT PERC", ui->spinBoxMktPerc,  API2::UI_ELEMENT_SPIN_BOX , API2::DATA_TYPE_INTEGER ,  API2::UI_STATE_ENABLED , API2::TABLE_STATE_SHOW , API2::DB_FEILD_SHOW, API2::UPDATE_STATE_ENABLE);
    _isTbt            = new API2::PARAM("isTbt", "IS TBT", ui->checkBoxIsTbt,  API2::UI_ELEMENT_CHECK_BOX , API2::DATA_TYPE_BOOLEAN ,  API2::UI_STATE_ENABLED , API2::TABLE_STATE_SHOW , API2::DB_FEILD_SHOW, API2::UPDATE_STATE_ENABLE);
    _currentSpread    = new API2::PARAM("currentSpread", "CURRENT SPREAD", NULL,  API2::UI_ELEMENT_NO_UI , API2::DATA_TYPE_DOUBLE ,  API2::UI_STATE_DISABLED , API2::TABLE_STATE_SHOW , API2::DB_FEILD_HIDE);
    makeParamList();
}
void FutFutParams::addParams(API2::PARAM *param, int columnIndex, short filterWidget,bool isEditable)
{

    _paramsMap.insert(param->getParamName(), param);
    param->setColumnIndex(columnIndex);
    param->setFilterType(filterWidget);
    param->setColumnEditable(isEditable);
}

void FutFutParams::makeParamList()
{
    short index=1;

    addParams(_transactionType);
    addParams(_clientId);
    addParams(_riskStatus);
    addParams(_sequenceNumber);
    addParams(_adminTokenId, index++);
    addParams(_strategyId,index++,API2::WidgetType_LINEEDIT);
    addParams(_state,index++);

    addParams(_symbolId,index++);
    addParams(_symbolName,index++);
    addParams(_mode, index++, API2::WidgetType_COMBOBOX);
    addParams(_symbolId2,index++);
    addParams(_symbolName2,index++);
    addParams(_mode2, index++, API2::WidgetType_COMBOBOX);

    _adminTokenId->setColumnHidden(true);
    _symbolId->setColumnHidden(true);
    _symbolId2->setColumnHidden(true);

    addParams(_portfolioId,index++);
    addParams(_strategyComment,index++);

    addParams(_totalLots, index++, API2::WidgetType_MAX, true);
    addParams(_orderLots, index++, API2::WidgetType_MAX, true);
    addParams(_desiredSpread , index++, API2::WidgetType_MAX, true);
    addParams(_marketPercentage, index++);
    addParams(_hedgeMethod, index++);
    addParams(_isTbt, index++);
    addParams(_currentSpread, index++);

}

