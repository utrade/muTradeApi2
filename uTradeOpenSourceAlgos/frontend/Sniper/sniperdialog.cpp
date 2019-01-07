#include "sniperdialog.h"
#include "ui_sniperdialog.h"
#include "F:/GUIR/gui/FrontEnd_Api_Includes/dll_includes/StrategyConstants.h"

#define SYMBOL_ID "SYMBOL LEG1"
#define ORDER_MODE "Order Mode 1"
#define ACC_DETAIL "Acc Detail 1"
#define QUANTITY "Quantity"
#define TRIGGER_PRICE "Trigger Price"
#define LIMIT_PRICE "Limit Price"

#define ORDER_TYPE "Order Type"

#define fileName "uTrade"

Sniperdialog :: Sniperdialog(QWidget *parent) :
    ui(new Ui::Sniperdialog), _updateCounter(0)
{
    ui->setupUi(this);

}

Sniperdialog :: ~Sniperdialog()
{
    delete ui;
}

/**
* Initialize and Displaying the window
*
* @brief initDisplay
*/

void Sniperdialog :: initDisplay(){
    initialize();
    setWindowFlags (windowFlags() | Qt::WindowMinimizeButtonHint );
    setWindowTitle("Sniper");
    show();

    raise();
    activateWindow();

}

/**
* Initialize first leg view, button panel and table view.
*
* @brief Initialize
*/

void Sniperdialog :: initialize()
{
    initializeSymbolPanel();

    ui->buttonPanel->addWidget(getBaseWrapper()->getButtonPanel());

    getBaseWrapper()->setStrategyContainer(ui->groupBoxStrategyContainer,NULL);

    getBaseWrapper()->hideButtons(API2::CTRL_BTN_SETTINGS);

    getBaseWrapper()->hideButtons(API2::CTRL_BTN_MINIMIZE);
    getBaseWrapper()->hideButtons(API2::CTRL_BTN_STOPALL);

    _Sniperparams = new Sniperparams(ui);

    setDefaultIndex();
    _paramsMap = & _Sniperparams->getParamList();

    getBaseWrapper()->addtoParamsGroup(_paramsMap);

    getBaseWrapper()->addToMainStrategyWindow(ui->verticalLayoutTableView);

    _baseTableModel = getBaseWrapper()->getTableModel();

    getBaseWrapper()->setStrategyInSingleRow(0);

    int index = ui->comboBoxMarket->findText(getBaseWrapper()->configFileValueStr("DEFAULT_MARKET"));
    ui->comboBoxMarket->setCurrentIndex(index == -1 ? 0 : index);

    //INITIALIZING TIMER.
    connect(&_timer, SIGNAL(timeout()), this, SLOT(updateDataOnTimer()));
    _timer.start(800);
    connect(ui->comboBoxMarket,SIGNAL(activated(int)),this,SLOT(setPrecisionDecimal(int)));

populateFilters();

}

void Sniperdialog::setPrecisionDecimal(int a)
{
    qlonglong symbolId=getBaseWrapper()->getLegsSymbolId(API2::FIRST_LEG);
    const  API2::SymbolDetail &sd =  getBaseWrapper()->getSymbolIdDetail(symbolId);
    if(!sd.flag)
        return;
    double stepSize = (double)sd.tickSize/sd.multiplier;
    int lotsize = sd.lotSize;
    qDebug()<<"in setprecision function"<<stepSize;
    ui->quantityspinbox->setValue(lotsize);
    ui->limitpricespinbox->setDecimals(sd.precision);
    ui->limitpricespinbox->setSingleStep(stepSize);
    ui->triggerpricespinbox->setDecimals(sd.precision);
    ui->triggerpricespinbox->setSingleStep(stepSize);

}


/**
* Initialize first leg symbol panel.
*
* @brief initializeSymbolPanel
*/

void Sniperdialog :: initializeSymbolPanel(){

    SymbolPanelElements *symbolPanelElements =new SymbolPanelElements(ui->comboBoxMod,
                                                                      ui->comboBoxSource,
                                                                      ui->comboBoxMarket,
                                                                      ui->comboBoxInstrument,
                                                                      ui->verticalLayoutSymbol,
                                                                      ui->comboBoxSeries,
                                                                      ui->comboBoxExpiry,
                                                                      ui->comboBoxOptMod,
                                                                      ui->comboBoxStrikePrice,
                                                                      ui->lineEditLotSize,
                                                                      ui->radioButtonClient,
                                                                      ui->radioButtonPro,
                                                                      ui->lineEditPartCode,
                                                                      ui->comboBoxClientCode);

    getBaseWrapper()->addSymbolPanel(API2::FUTURE | API2::STOCK | API2::OPTION ,symbolPanelElements,true);
    getBaseWrapper()->initializeFirstLegSignals();
}

void Sniperdialog::updateEditableFieldColor(int row, QColor color)
{
    getBaseWrapper()->setColumnBackGround(row,_Sniperparams->_quantity->getColumnIndex(),color);

    getBaseWrapper()->setColumnBackGround(row,_Sniperparams->_triggerprice->getColumnIndex(),color);
    getBaseWrapper()->setColumnBackGround(row,_Sniperparams->_limitprice->getColumnIndex(),color);

}

/**
  *@brief  populateFilters
  *populate FilterWidgets with data
  */
void Sniperdialog::populateFilters()
{
    QComboBox *filterComboBox;

    filterComboBox =  getBaseWrapper()->getFilterWidgetComboBox(_Sniperparams->_state->getColumnIndex());
    filterComboBox->addItem(STRATEGY_CONST::ALL);
    filterComboBox->addItem(STRATEGY_CONST::READY_STATE);
    filterComboBox->addItem(STRATEGY_CONST::RUN_STATE);
    filterComboBox->addItem(STRATEGY_CONST::AWAITED);
    filterComboBox->setCurrentIndex(0);

    filterComboBox = getBaseWrapper()->getFilterWidgetComboBox(_Sniperparams->_mode->getColumnIndex());
    filterComboBox->addItem(STRATEGY_CONST::ALL);
    filterComboBox->addItem("Buy");
    filterComboBox->addItem("Sell");
    filterComboBox->setCurrentIndex(0);
}

/**
* This function call, when user click on add button. It perform UI parameter validation, add data into model-view class, and store data into database.
*
* @brief onAddPushButtonClicked
*/
void Sniperdialog :: onAddPushButtonClicked(){

    getBaseWrapper()->on_AddPushButton_Clicked();

}

/**
* get UI parameter
*
* @brief buildCommandFromUI
*
* @param state : UI state of portfolio.
*/

bool Sniperdialog :: buildCommandFromUi(API2::PORTFOLIO_STATE state)
{
    _Sniperparams->_adminTokenId->setValue(0);
    _Sniperparams->_clientId->setValue(getBaseWrapper()->getUserId());
    _Sniperparams->_strategyId->setValue(0);
    _Sniperparams->_riskStatus->setValue(API2::CONSTANTS::RSP_RiskStatus_MAX);
    _Sniperparams->_portfolioId->setValue(getBaseWrapper()->getPortFolioId());
    _Sniperparams->_state->setValue(API2::CONSTANTS::RSP_ResponseType_MAX);
    _Sniperparams->_strategyComment->setValue(API2::CONSTANTS::RSP_StrategyComment_MAX);
    _Sniperparams->_transactionType->setValue(API2::CONSTANTS::CMD_TransactionType_NEW);
    _Sniperparams->_sequenceNumber->setValue(0);

    qlonglong symbolId = getBaseWrapper()->getLegsSymbolId(API2::FIRST_LEG);
    const API2:: SymbolDetail &sd = getBaseWrapper()->getSymbolIdDetail(symbolId);

    _Sniperparams->_symbolId->setValue(symbolId);
    _Sniperparams->_symbolName->setValue(sd.scripName);
    _Sniperparams->_orderType->setValue(ui->comboBoxOrderType->currentIndex());
    _Sniperparams->_mode->setValue(ui->comboBoxMod->currentIndex());
    _Sniperparams->_quantity->setValue(ui->quantityspinbox->value());
    _Sniperparams->_triggerprice->setValue(double(ui->triggerpricespinbox->value()*100));
    _Sniperparams->_limitprice->setValue(double(ui->limitpricespinbox->value())*100);
    return true;
}

/**
    set default Index which are directly accessible.
    @brief setDefaultIndex
**/

void Sniperdialog :: setDefaultIndex()
{
    getBaseWrapper()->_col.adminTokenIdIndex    = _Sniperparams->_adminTokenId->getColumnIndex();
    getBaseWrapper()->_col.stateIndex           = _Sniperparams->_state->getColumnIndex();
    getBaseWrapper()->_col.strategyIdIndex      = _Sniperparams->_strategyId->getColumnIndex();
    getBaseWrapper()->_col.strategyCommentIndex = _Sniperparams->_strategyComment->getColumnIndex();
    getBaseWrapper()->_col.portFolioIdIndex     = _Sniperparams->_portfolioId->getColumnIndex();
    getBaseWrapper()->_col.symbolIdLeg1         = _Sniperparams->_symbolId->getColumnIndex();
}


/**
* allow spread calculation.
*
* @brief isSpreadCalculationAllowed
*
* @return bool
*/


bool Sniperdialog :: isSpreadCalculationAllowed()
{
    return false;
}


/**
*
* when user update row element this function called. this function is used to update parameter can not be update by using base strategy.
*
* @brief updateRemainingFields
*
**/

void Sniperdialog :: updateRemainingFeilds(int row, QSqlRecord &adminTokenIdData)
{
    getBaseWrapper()->setTableData(row,
                                   _Sniperparams->_symbolName->getColumnIndex(),
                                   getBaseWrapper()->getScripName(adminTokenIdData.value(_Sniperparams->_symbolId->getParamName()).toLongLong ()));

    getBaseWrapper()->setTableData(row,_Sniperparams->_state->getColumnIndex(),
                                   getCommonMethodsWrapper()->getStrategyState(adminTokenIdData.value(_Sniperparams->_state->getParamName()).toInt()));}

/**
  remove selected row.

  @brief onRemovePushButtonClicked
**/
void Sniperdialog :: onRemovePushButtonClicked()
{
    getBaseWrapper()->on_RemovePushButton_Clicked();
}

/**
  enable symbol panel for creating new strategy row. From there user can give input and can add new strategy row.

  @brief onNewPushButtonClicked

**/

void Sniperdialog :: onNewPushButtonClicked(){
    getBaseWrapper()->enableSymbolPanel(API2::FIRST_LEG, true);
    getBaseWrapper()->on_NewPushButton_Clicked();
}

/**
  edit a selected row.

  @brief onEditPushButtonCLicked

**/

void Sniperdialog :: onEditPushButtonClicked()
{
    QModelIndex index = getBaseWrapper()->getCurrentIndex();
    if(index.isValid())
    {
        getBaseWrapper()->on_EditPushButton_Clicked(index.row());
        getBaseWrapper()->enableSymbolPanel(API2::FIRST_LEG, false);
    }
}

/**
  commit changes when user edit selected row.

  @brief onCommitPushButtonClicked

**/

void Sniperdialog :: onCommitPushButtonClicked()
{
    QModelIndex index = getBaseWrapper()->getCurrentIndex();
    if(!index.isValid()) return;

    getBaseWrapper()->on_CommitPushButton_Clicked();
}

/**
  validate UI parameer when user add new strategy or edit exiting strategy.

  @brief validateData

  @param state : Ui state of portfolio
**/

bool Sniperdialog :: validateData(API2::PORTFOLIO_STATE state)
{
    if(!getBaseWrapper()-> validateData(API2::FIRST_LEG))
    {
        QMessageBox :: warning (this, fileName, "fill all parameter");
        return false;
    }
    qlonglong symbolId = getBaseWrapper()->getLegsSymbolId(API2::FIRST_LEG);
    const API2:: SymbolDetail &sd = getBaseWrapper()->getSymbolIdDetail(symbolId);
    qlonglong quantity = QString::number(ui->quantityspinbox->value(),'f',sd.precision).remove(".").toLongLong();
    qreal triggerPrice = ui->triggerpricespinbox->value();
    qreal limitPrice = ui->limitpricespinbox->value();
    uint buy=ui->comboBoxMod->currentIndex();
    qDebug()<<"trigger price:"<<triggerPrice;
    qDebug()<<"limitprice:"<<limitPrice;

    if(!quantity){
        QMessageBox :: warning (this, fileName, "quantity can not be zero.");
        return false;
    }
    if(buy==0){
    if(!triggerPrice || !limitPrice || triggerPrice<limitPrice){
        QMessageBox::warning(this, fileName, "Trigger Price must be greater than Limit Price");
        return false;}
    }
    if(buy==1)
    {
        if(!triggerPrice || !limitPrice || triggerPrice>limitPrice){
            QMessageBox::warning(this, fileName, "Limit Price must be greater than Trigger Price");
            return false;}
    }
    return true;
}


/**

  when user change in editable box of any row, then to save changes this function is called.

  @brief onALtPressed

**/

void Sniperdialog :: onAltMPressed(){
    QModelIndex index = getBaseWrapper()->getCurrentIndex();

    if(!index.isValid()) return;
    int row = index.row();

    qlonglong quantity = getBaseWrapper()->getTableData(row,_Sniperparams->_quantity->getColumnIndex()).toLongLong();
    qreal triggerPrice = getBaseWrapper()->getTableData(row,_Sniperparams->_triggerprice->getColumnIndex()).toDouble();
    qreal limitPrice = getBaseWrapper()->getTableData(row,_Sniperparams->_limitprice->getColumnIndex()).toDouble();

    if(!quantity){
        QMessageBox :: warning (this, fileName, "quantity can not be zero.");
        return;
    }
    if(!triggerPrice || !limitPrice || triggerPrice >= limitPrice){
        QMessageBox::warning(this, fileName, "Limit Price must be greater than or equal to Trigger Price");
        return;
    }

    const API2::  SymbolDetail &sd = getBaseWrapper()->getSymbolIdDetail(
                getBaseWrapper()->getTableData(row,_Sniperparams->_symbolId->getColumnIndex()).toLongLong());

    ui->quantityspinbox->setValue(quantity);
    ui->triggerpricespinbox->setValue(triggerPrice);
    ui->limitpricespinbox->setValue(limitPrice);

    if(getBaseWrapper()->getTableData(row,_Sniperparams->_state->getColumnIndex())==STRATEGY_CONST::RUN_STATE)
        getBaseWrapper()->runStrategy(row,false,true);
    else
        getBaseWrapper()->on_CommitPushButton_Clicked();


}

/**
*   minimize the window
*
* @brief onEscapePressed

**/

void Sniperdialog :: onEscapePressed()
{
    getBaseWrapper()->onEscapePressed();
}


/**
* run or terminate the strategy when user press ctrl+space button.
*
* @brief onCtrlSpacePressed
**/
void Sniperdialog::onCtrlSpacePressed()
{
    getBaseWrapper()->onCtrlSpacePressed();
}

/**
   hide or show the symbol panel when user press Alt+Up key.

   @brief onUpKeyPressed
**/

void Sniperdialog::onUpKeyPressed()
{
    getBaseWrapper()->onUpKeyPressed();
}

/**
*   for run and modify the strategy.
*
*   @brief onRunPushButtonClicked

**/
void Sniperdialog :: onRunPushButtonClicked()
{
    QModelIndex index =  getBaseWrapper()->getCurrentIndex();
    if(index.isValid())
    {

        getBaseWrapper()->runStrategy(index.row());

    }
    getBaseWrapper()->updateTableView();
}

/**
* set command that are interact with backend
*
* @brief SetApiCommand
*
* @param apiParams : User params to interact with backend.
* @param  record : record of a row.
* @param  type : transaction type
*
**/

void Sniperdialog :: setApiCommand(API2::UserParams *apiParams, QSqlRecord &record, int stgCount, short type)
{
    getBaseWrapper()->setCommandCategory(API2::CONSTANTS::CMD_CommandCategory_API2_STRATEGY);
    qlonglong adminTokenId = record.value(_Sniperparams->_adminTokenId->getParamName()).toLongLong();
    apiParams->setAdminTokenId(adminTokenId);
    apiParams->setClientId(getBaseWrapper()->getUserId());
    apiParams->setSequenceNumber(0);
    apiParams->setStrategyId(record.value(_Sniperparams->_strategyId->getParamName()).toLongLong());
    apiParams->setTransactionType(type);
    apiParams->setStrategyVersion(0);

    apiParams->setValue(SYMBOL_ID, record.value(_Sniperparams->_symbolId->getParamName()).toLongLong());

    apiParams->setValue(ORDER_MODE,TO_QT_COMPATIBLE_ASCII( record.value(_Sniperparams->_mode->getParamName()).toChar() ) );
    apiParams->setValue(ACC_DETAIL,getBaseWrapper()->getAccountDetailFromDb(adminTokenId,API2::FIRST_LEG));

        apiParams->setValue(QUANTITY,(record.value( _Sniperparams->_quantity->getParamName()).toLongLong()));
        apiParams->setValue(ORDER_TYPE,TO_QT_COMPATIBLE_ASCII(record.value( _Sniperparams->_orderType->getParamName()).toChar()));
        apiParams->setValue(TRIGGER_PRICE,long long int(record.value( _Sniperparams->_triggerprice->getParamName()).toDouble()));
        apiParams->setValue(LIMIT_PRICE,long long int(record.value( _Sniperparams->_limitprice->getParamName()).toDouble()));
#ifdef DEBUG
    apiParams->dump();
#endif

}

/**
*  when user run any strategy. it give response back to the client. this function handle response from back end.
*
* @brief RecieveStrategyResponse
*
* @param strategyResponse
*
**/


void Sniperdialog :: receiveStrategyResponse(API2::Strategy &strategyResponse)
{
    QSharedPointer<API2::Strategy>  strategyResponseSharedPtr  = QSharedPointer<API2::Strategy>(new API2::Strategy(strategyResponse));
    getBaseWrapper()->receiveStrategyResponse(strategyResponseSharedPtr);
}



/**
*   when user client on the EDIT button, to set parameter in common symbol panel of the selected row.
*
*  @brief populateUIPanels
*
*  @param row : selected row number
*  @param record : stored record of selected row
*  @param isNewState

**/
void Sniperdialog::populateUIPanels(int row,QSqlRecord &record,bool isNewState)
{

    if(row ==-1)
    {
        return;
    }

    ui->quantityspinbox->setValue(QString::number((double)record.value(
                                                       _Sniperparams->_quantity->getParamName()).toLongLong(),'f').toDouble());

    ui->triggerpricespinbox->setValue(QString::number((double)record.value(
                                                       _Sniperparams->_triggerprice->getParamName()).toDouble(),'f').toDouble()/100);
    ui->limitpricespinbox->setValue(QString::number((double)record.value(
                                                       _Sniperparams->_limitprice->getParamName()).toDouble(),'f').toDouble()/100);
}


/**
    update displayed data after every 800ms.

    @brief updateDataOnTimer
**/

void Sniperdialog::updateDataOnTimer()
{
    bool  _isNewStrategyWriteMethod = getBaseWrapper()->configFileValue("NEW_STRATEGY_WRITE_METHOD");
    if(!_isNewStrategyWriteMethod)
    {
        while(!getBaseWrapper()->_responseQueue.isEmpty())
        {
            getBaseWrapper()->updateResponse(getBaseWrapper()->_responseQueue.dequeue());
            if(_updateCounter++==8){
                break;
            }
        }
    }
    if(!getBaseWrapper()->isProcessingEvent())
        getBaseWrapper()->updateTableView();
}

/**
    if portfolio name is present in strategy
    @brief isPortfolioNamePresent
**/
bool Sniperdialog :: isPortfolioNamePresent()
{
    return false;
}

/**
    if total quantity allowed in strategy
    @brief isSidTotalQtyHandling
    @return : true :- is allowed.
              false :- if not allowed.
**/
bool Sniperdialog :: isSidTotalQtyHandling()
{
    return false;
}

void Sniperdialog :: getDllVersionString(QString &dllVersionString)
{
    dllVersionString = DLL_VERSION_STRING;
}

extern "C" __declspec(dllexport) void* createObject()
{
    Sniperdialog *ptr = new Sniperdialog();
    return (void *)ptr;
}

void Sniperdialog::on_pushButtonClose_clicked()
{
    ui->pushButtonClose->setText(ui->groupBoxStrategyContainer->isVisible() ? "+" : "-");
    ui->groupBoxStrategyContainer->setVisible(!ui->groupBoxStrategyContainer->isVisible());
}

bool Sniperdialog::isStrategyLegPresent()
{
    return false;
}
