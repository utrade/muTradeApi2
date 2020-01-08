#include "uilibrary.h"
#include "ui_uilibrary.h"
#include "../includes/dll_includes/StrategyConstants.h"

#define SYMBOL_ID "SYMBOL LEG1"
#define ORDER_MODE "Order Mode 1"
#define ACC_DETAIL "Acc Detail 1"
#define SYMBOL_ID_2 "SYMBOL LEG2"
#define ORDER_MODE_2 "Order Mode 2"
#define ACC_DETAIL_2 "Acc Detail 2"
#define TOTAL_LOTS "TotalQuantity"
#define ORDER_LOTS "OrderQuantity"
#define DESIRED_SPREAD "Desired Spread"
#define MARKET_PERCENTAGE "Market Percentage"
#define HEDGE_METHOD "Hedge Method"
#define IS_TBT "isTBT"
#define CURRENT_SPREAD "currentSpread"



UiLibrary :: UiLibrary(QWidget *parent) :
    ui(new Ui::UiLibrary), _updateCounter(0)
{
    ui->setupUi(this);
}

UiLibrary :: ~UiLibrary()
{
    delete ui;
}

/**
* Initialize and Displaying the window
*
* @brief initDisplay
*/

void UiLibrary :: initDisplay(){
    initialize();
    initializeFilter();
    setWindowFlags (windowFlags() | Qt::WindowMinimizeButtonHint );
    setWindowTitle("Sample Strategy");
    show();

    raise();
    activateWindow();

}

/**
* Initialize first leg view, button panel and table view.
*
* @brief Initialize
*/

void UiLibrary :: initialize()
{
    initializeSymbolPanel();

    ui->buttonPanel->addWidget(getBaseWrapper()->getButtonPanel());

    ui->labelSource->setVisible(getBaseWrapper()->configFileValue("DISPLAY_SOURCE"));

    getBaseWrapper()->setStrategyContainer(ui->groupBoxShowHide,NULL);

    getBaseWrapper()->hideButtons(API2::CTRL_BTN_SETTINGS);

    getBaseWrapper()->hideButtons(API2::CTRL_BTN_STOPALL);

    _futfutParams = new FutFutParams(ui);

    setDefaultIndex();
    _paramsMap = & _futfutParams->getParamList();

    getBaseWrapper()->addtoParamsGroup(_paramsMap);

    getBaseWrapper()->addToMainStrategyWindow(ui->verticalLayoutTableView);

    _baseTableModel = getBaseWrapper()->getTableModel();

    getBaseWrapper()->setStrategyInSingleRow(0);

    int index = ui->comboBoxExchange->findText(getBaseWrapper()->configFileValueStr("DEFAULT_MARKET"));
    ui->comboBoxExchange->setCurrentIndex(index == -1 ? 0 : index);
    ui->comboBoxExchange2->setCurrentIndex(index == -1 ? 0 : index);
    ui->doubleSpinBoxDesiredSpread->setSingleStep(0.05);

    QStringList list;
    list.append("Best BID/ASK");
    list.append("Market Order");
    ui->comboBoxHedgeMethod->addItems(list);

    //INITIALIZING TIMER.
    connect(&_timer, SIGNAL(timeout()), this, SLOT(updateDataOnTimer()));
    _timer.start(800);

}


/**
* Initialize first leg symbol panel.
*
* @brief initializeSymbolPanel
*/

void UiLibrary :: initializeSymbolPanel(){

    SymbolPanelElements *symbolPanelElements =  new SymbolPanelElements(ui->comboBoxMode,
                                                                        ui->comboBoxSource,
                                                                        ui->comboBoxExchange,
                                                                        ui->comboBoxInstrument,
                                                                        ui->verticalLayoutSymbol,
                                                                        ui->comboBoxSeries,
                                                                        ui->comboBoxExpiryDate,
                                                                        ui->comboBoxOptType,
                                                                        ui->comboBoxStrikePrice,
                                                                        ui->lineEditLotSize,
                                                                        ui->radioButtonClient,
                                                                        ui->radioButtonPro,
                                                                        ui->lineEditPartCode,
                                                                        ui->comboBoxClientCode);

    SymbolPanelElements *symbolPanelElements2 = new SymbolPanelElements(ui->comboBoxMode2,
                                                                        ui->comboBoxSource2,
                                                                        ui->comboBoxExchange2,
                                                                        ui->comboBoxInstrument2,
                                                                        ui->verticalLayoutSymbol2,
                                                                        ui->comboBoxSeries2,
                                                                        ui->comboBoxExpiryDate2,
                                                                        ui->comboBoxOptType2,
                                                                        ui->comboBoxStrikePrice2,
                                                                        ui->lineEditLotSize2,
                                                                        ui->radioButtonClient2,
                                                                        ui->radioButtonPro2,
                                                                        ui->lineEditPartCode2,
                                                                        ui->comboBoxClientCode2);

    getBaseWrapper()->addSymbolPanel(API2::FUTURE | API2::STOCK | API2::OPTION,
                                     symbolPanelElements, true);
    getBaseWrapper()->initializeFirstLegSignals();

    getBaseWrapper()->addSymbolPanel(API2::FUTURE | API2::STOCK | API2::OPTION,
                                     symbolPanelElements2, true);
    getBaseWrapper()->initializeSecondLegSignals();
}


/**
* Initialize Filters for table view
* @brief initializeFilter
*/
void UiLibrary::initializeFilter()
{
    QStringList filterList;
    filterList.append(STRATEGY_CONST::ALL);
    filterList.append(getCommonMethodsWrapper()->getOrderMode(API2::DllCMD::OrderMode_BUY));
    filterList.append(getCommonMethodsWrapper()->getOrderMode(API2::DllCMD::OrderMode_SELL));
    QComboBox* comboBox = getBaseWrapper()->getFilterWidgetComboBox(_futfutParams->_mode->getColumnIndex());
    if(comboBox)
    {
        comboBox->addItems(filterList);
        comboBox->setCurrentIndex(0);
    }

    comboBox = getBaseWrapper()->getFilterWidgetComboBox(_futfutParams->_mode2->getColumnIndex());
    if(comboBox)
    {
        comboBox->addItems(filterList);
        comboBox->setCurrentIndex(0);
    }
}


/**
* This function call, when user click on add button. It perform UI parameter validation, add data into model-view class, and store data into database.
*
* @brief onAddPushButtonClicked
*/


void UiLibrary :: onAddPushButtonClicked(){

    getBaseWrapper()->on_AddPushButton_Clicked();

}

/**
* get UI parameter
*
* @brief buildCommandFromUI
*
* @param state : UI state of portfolio.
*/

bool UiLibrary :: buildCommandFromUi(API2::PORTFOLIO_STATE state)
{
    _futfutParams->_adminTokenId->setValue(0);
    _futfutParams->_clientId->setValue(getBaseWrapper()->getUserId());
    _futfutParams->_strategyId->setValue(0);
    _futfutParams->_riskStatus->setValue(API2::CONSTANTS::RSP_RiskStatus_MAX);
    _futfutParams->_portfolioId->setValue(getBaseWrapper()->getPortFolioId());
    _futfutParams->_state->setValue(API2::CONSTANTS::RSP_ResponseType_MAX);
    _futfutParams->_strategyComment->setValue(API2::CONSTANTS::RSP_StrategyComment_MAX);
    _futfutParams->_transactionType->setValue(API2::CONSTANTS::CMD_TransactionType_NEW);
    _futfutParams->_sequenceNumber->setValue(0);

    qlonglong symbolId = getBaseWrapper()->getLegsSymbolId(API2::FIRST_LEG);
    qlonglong symbolId2 = getBaseWrapper()->getLegsSymbolId(API2::SECOND_LEG);
    const API2:: SymbolDetail &sd = getBaseWrapper()->getSymbolIdDetail(symbolId);
    const API2:: SymbolDetail &sd2 = getBaseWrapper()->getSymbolIdDetail(symbolId2);

    _futfutParams->_symbolId->setValue(symbolId);
    _futfutParams->_symbolName->setValue(sd.scripName);
    _futfutParams->_symbolId2->setValue(symbolId2);
    _futfutParams->_symbolName2->setValue(sd2.scripName);

    _futfutParams->_mode->setValue(ui->comboBoxMode->currentIndex());
    _futfutParams->_mode2->setValue(ui->comboBoxMode2->currentIndex());
    _futfutParams->_totalLots->setValue(ui->spinBoxTotalLots->value());
    _futfutParams->_orderLots->setValue(ui->spinBoxOrderLots->value());

    _futfutParams->_desiredSpread->setValue(ui->doubleSpinBoxDesiredSpread->text().remove(QLocale::system().decimalPoint()).toLongLong());
    _futfutParams->_marketPercentage->setValue(ui->spinBoxMktPerc->text().remove(QLocale::system().decimalPoint()).toLongLong());
    _futfutParams->_hedgeMethod->setValue(ui->comboBoxHedgeMethod->currentText());
    _futfutParams->_isTbt->setValue(ui->checkBoxIsTbt->isChecked());

    return true;
}

/**
    set default Index which are directly accessible.
    @brief setDefaultIndex
**/

void UiLibrary :: setDefaultIndex()
{
    getBaseWrapper()->_col.adminTokenIdIndex    = _futfutParams->_adminTokenId->getColumnIndex();
    getBaseWrapper()->_col.stateIndex           = _futfutParams->_state->getColumnIndex();
    getBaseWrapper()->_col.strategyIdIndex      = _futfutParams->_strategyId->getColumnIndex();
    getBaseWrapper()->_col.strategyCommentIndex = _futfutParams->_strategyComment->getColumnIndex();
    getBaseWrapper()->_col.portFolioIdIndex     = _futfutParams->_portfolioId->getColumnIndex();
    getBaseWrapper()->_col.symbolIdLeg1         = _futfutParams->_symbolId->getColumnIndex();
}


/**
* allow spread calculation.
*
* @brief isSpreadCalculationAllowed
*
* @return bool
*/


bool UiLibrary :: isSpreadCalculationAllowed()
{
    return false;
}

/**
* modify symbol Id detail of particular row in table.
*
* @brief updateSymbolIdsDetail
* @param row : row number of perticular symbol Id.
*/

void UiLibrary:: updateSymbolIdsDetail(int row, bool isUpdateAll)
{

    if(row==-1) return;
    int start=row;
    int end =row+1;
    if(isUpdateAll)
    {
        start = 0;
        end = _baseTableModel->rowCount();
        getBaseWrapper()->_hashRowSymboID.clear();
        getBaseWrapper()->_hashRowSpreadDetail.clear();
    }


    for(int counter = start; counter < end; ++counter)
    {
        getBaseWrapper()->insertHashRowSymbolId(counter, _futfutParams->_symbolId2->getColumnIndex(), 0);
        getBaseWrapper()->insertHashRowSymbolId(counter,
                                                _futfutParams->_symbolId->getColumnIndex(),
                                                _baseTableModel->item(counter,_futfutParams->_totalLots->getColumnIndex())->data(Qt::DisplayRole).toLongLong());
    }
}


/**
*
* when user update row element this function called. this function is used to update parameter can not be update by using base strategy.
*
* @brief updateRemainingFields
*
**/

void UiLibrary :: updateRemainingFeilds(int row, QSqlRecord &adminTokenIdData)
{
    getBaseWrapper()->setTableData(row, _futfutParams->_symbolName->getColumnIndex(),
                                   getBaseWrapper()->getScripName(adminTokenIdData.value(_futfutParams->_symbolId->getParamName()).toLongLong ()));

    getBaseWrapper()->setTableData(row, _futfutParams->_symbolName2->getColumnIndex(),
                                   getBaseWrapper()->getScripName(adminTokenIdData.value(_futfutParams->_symbolId2->getParamName()).toLongLong ()));

    getBaseWrapper()->setTableData(row,_futfutParams->_state->getColumnIndex(),
                                   getCommonMethodsWrapper()->getStrategyState(adminTokenIdData.value(_futfutParams->_state->getParamName()).toInt()));}

/**
  remove selected row.

  @brief onRemovePushButtonClicked
**/
void UiLibrary :: onRemovePushButtonClicked()
{
    getBaseWrapper()->on_RemovePushButton_Clicked();
}

/**
  enable symbol panel for creating new strategy row. From there user can give input and can add new strategy row.

  @brief onNewPushButtonClicked

**/

void UiLibrary :: onNewPushButtonClicked(){
    getBaseWrapper()->enableSymbolPanel(API2::FIRST_LEG, true);
    getBaseWrapper()->enableSymbolPanel(API2::SECOND_LEG, true);
    getBaseWrapper()->on_NewPushButton_Clicked();
}

/**
  edit a selected row.

  @brief onEditPushButtonCLicked

**/

void UiLibrary :: onEditPushButtonClicked()
{
    QModelIndex index = getBaseWrapper()->getCurrentIndex();
    if(index.isValid())
    {
        getBaseWrapper()->on_EditPushButton_Clicked(index.row());
        getBaseWrapper()->enableSymbolPanel(API2::FIRST_LEG, false);
        getBaseWrapper()->enableSymbolPanel(API2::SECOND_LEG, false);
    }
}

/**
  commit changes when user edit selected row.

  @brief onCommitPushButtonClicked

**/

void UiLibrary :: onCommitPushButtonClicked()
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

bool UiLibrary :: validateData(API2::PORTFOLIO_STATE state)
{
    if(!(getBaseWrapper()->validateData(API2::FIRST_LEG) &&
         getBaseWrapper()->validateData(API2::SECOND_LEG)))
    {
        QMessageBox :: warning (this, fileName, "Incorrect Symbol Legs.");
        return false;
    }
    qlonglong symbolId = getBaseWrapper()->getLegsSymbolId(API2::FIRST_LEG);
    qlonglong symbolId2 = getBaseWrapper()->getLegsSymbolId(API2::SECOND_LEG);

    if(symbolId == symbolId2)
    {
        QMessageBox :: warning(this, fileName, "Both legs need to be different.");
        return false;
    }
    const API2:: SymbolDetail &sd = getBaseWrapper()->getSymbolIdDetail(symbolId);
    qlonglong totalLots = ui->spinBoxTotalLots->value();
    qlonglong orderLots = ui->spinBoxOrderLots->value();
    qlonglong desiredSpread = ui->doubleSpinBoxDesiredSpread->text().remove(QLocale::system().decimalPoint()).toLongLong();

    if(!desiredSpread)
    {
        QMessageBox :: warning (this, fileName, "Desired Spread can not be zero.");
        return false;
    }
    if(desiredSpread % sd.tickSize != 0)
    {
        QMessageBox :: warning (this, fileName, "Desired Spread not in tick size.");
        return false;
    }
    if(!totalLots || !orderLots || totalLots < orderLots){
        QMessageBox::warning(this, fileName, "Total lots must be greater than Order Lots");
        return false;
    }
    return true;
}

/**
*  when user save a portfolio, set some default value for the database.
*
*  @brief setPortfolioDefaultValues
*
*  @param portfolioRow : list of portfolio row.
**/


void UiLibrary::setPortfolioDefaultValues(QStringList &portfolioRow)
{
    Q_UNUSED(portfolioRow);
}

/**

**/
void UiLibrary::firstLegSymbolChanged()
{
    const API2::SymbolDetail& sd = getBaseWrapper()->getSymbolIdDetail(
                getBaseWrapper()->getLegsSymbolId(API2::FIRST_LEG));
    ui->spinBoxTotalLots->setMinimum(sd.lotSize);
    ui->spinBoxOrderLots->setMinimum(sd.lotSize);
    ui->spinBoxTotalLots->setSingleStep(sd.lotSize);
    ui->spinBoxOrderLots->setSingleStep(sd.lotSize);
    ui->doubleSpinBoxDesiredSpread->setValue(0);
    ui->doubleSpinBoxDesiredSpread->setSingleStep(sd.tickSize / sd.multiplier);
}

/**

  when user change in editable box of any row, then to save changes this function is called.

  @brief onAltMPressed

**/

void UiLibrary :: onAltMPressed()
{
    QModelIndex index = getBaseWrapper()->getCurrentIndex();

    if(!index.isValid()) return;
    int row = index.row();

    qlonglong totalLots = getBaseWrapper()->getTableData(row,_futfutParams->_totalLots->getColumnIndex()).toLongLong();
    qlonglong orderLots = getBaseWrapper()->getTableData(row,_futfutParams->_orderLots->getColumnIndex()).toLongLong();
    qlonglong desiredSpread = getBaseWrapper()->getTableData(
                row,_futfutParams->_desiredSpread->getColumnIndex()).
            toString().remove(QLocale::system().decimalPoint()).toLongLong();

    if(!desiredSpread)
    {
        QMessageBox :: warning (this, fileName, "Desired Spread can not be zero.");
        return;
    }

    if( !totalLots || !orderLots ||totalLots < orderLots)
    {
        QMessageBox::warning(this,fileName,"Total Lots must be greater than or equal to  order lots");
        return ;
    }

    const API2::  SymbolDetail &sd = getBaseWrapper()->getSymbolIdDetail(
                getBaseWrapper()->getTableData(row,_futfutParams->_symbolId->getColumnIndex()).toLongLong());

    ui->spinBoxTotalLots->setValue(totalLots);
    ui->spinBoxOrderLots->setValue(orderLots);
    ui->doubleSpinBoxDesiredSpread->setValue(double(desiredSpread)/sd.multiplier);

    if(getBaseWrapper()->getTableData(row,_futfutParams->_state->getColumnIndex())==STRATEGY_CONST::RUN_STATE)
        getBaseWrapper()->runStrategy(row,false,true);
    else
        getBaseWrapper()->on_CommitPushButton_Clicked();


}

/**
*   minimize the window
*
* @brief onEscapePressed

**/

void UiLibrary :: onEscapePressed()
{
    getBaseWrapper()->onEscapePressed();
}


/**
* run or terminate the strategy when user press ctrl+space button.
*
* @brief onCtrlSpacePressed
**/
void UiLibrary::onCtrlSpacePressed()
{
    getBaseWrapper()->onCtrlSpacePressed();
}

/**
   hide or show the symbol panel when user press Alt+Up key.

   @brief onUpKeyPressed
**/

void UiLibrary::onUpKeyPressed()
{
    getBaseWrapper()->onUpKeyPressed();
}

/**
*   for run and modify the strategy.
*
*   @brief onRunPushButtonClicked

**/
void UiLibrary :: onRunPushButtonClicked()
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
* @param sampleCommand : User params to interact with backend.
* @param  record : record of a row.
* @param  type : transaction type
*
**/

void UiLibrary :: setApiCommand(API2::UserParams *sampleCommand, QSqlRecord &record, int stgCount, short type)
{
    getBaseWrapper()->setCommandCategory(API2::CONSTANTS::CMD_CommandCategory_API2_STRATEGY);
    qlonglong adminTokenId = record.value(_futfutParams->_adminTokenId->getParamName()).toLongLong();
    sampleCommand->setAdminTokenId(adminTokenId);
    sampleCommand->setClientId(getBaseWrapper()->getUserId());
    sampleCommand->setSequenceNumber(0);
    sampleCommand->setStrategyId(record.value(_futfutParams->_strategyId->getParamName()).toLongLong());
    sampleCommand->setTransactionType(type);
    sampleCommand->setStrategyVersion(0);

    sampleCommand->setValue(SYMBOL_ID, record.value(_futfutParams->_symbolId->getParamName()).toLongLong());
    sampleCommand->setValue(SYMBOL_ID_2, record.value(_futfutParams->_symbolId2->getParamName()).toLongLong());

    sampleCommand->setValue(ORDER_MODE,TO_QT_COMPATIBLE_ASCII( record.value(_futfutParams->_mode->getParamName()).toChar() ) );
    sampleCommand->setValue(ACC_DETAIL,getBaseWrapper()->getAccountDetailFromDb(adminTokenId,API2::FIRST_LEG));
    sampleCommand->setValue(ORDER_MODE_2,TO_QT_COMPATIBLE_ASCII( record.value(_futfutParams->_mode2->getParamName()).toChar() ) );
    sampleCommand->setValue(ACC_DETAIL_2,getBaseWrapper()->getAccountDetailFromDb(adminTokenId,API2::SECOND_LEG));

    sampleCommand->setValue(TOTAL_LOTS,(record.value( _futfutParams->_totalLots->getParamName()).toLongLong()));
    sampleCommand->setValue(ORDER_LOTS,(record.value( _futfutParams->_orderLots->getParamName()).toLongLong()));

    sampleCommand->setValue(DESIRED_SPREAD, record.value( _futfutParams->_desiredSpread->getParamName()).toLongLong());
    sampleCommand->setValue(MARKET_PERCENTAGE, record.value( _futfutParams->_marketPercentage->getParamName()).toLongLong());
    int index = ui->comboBoxHedgeMethod->findText(record.value( _futfutParams->_hedgeMethod->getParamName()).toString());
    index = (index == -1) ? 0 : index;
    sampleCommand->setValue(HEDGE_METHOD, TO_QT_COMPATIBLE_ASCII(QChar(index)));
    sampleCommand->setValue(IS_TBT, TO_QT_COMPATIBLE_ASCII(record.value( _futfutParams->_isTbt->getParamName()).toChar()));
    sampleCommand->setValue(CURRENT_SPREAD, 0);
}

/**
*  when user run any strategy. it give response back to the client. this function handle response from back end.
*
* @brief RecieveStrategyResponse
*
* @param strategyResponse
*
**/


void UiLibrary :: receiveStrategyResponse(API2::Strategy &strategyResponse)
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
void UiLibrary::populateUIPanels(int row,QSqlRecord &record,bool isNewState)
{

    if(row ==-1)
    {
        return;
    }

    const API2::SymbolDetail& sd = getBaseWrapper()->getSymbolIdDetail(record.value(_futfutParams->_symbolId->getParamName()).toLongLong());

    ui->spinBoxTotalLots->setValue(record.value(_futfutParams->_totalLots->getParamName()).toLongLong());

    ui->spinBoxOrderLots->setValue(record.value(_futfutParams->_orderLots->getParamName()).toLongLong());

    ui->doubleSpinBoxDesiredSpread->setValue(record.value(_futfutParams->_desiredSpread->getParamName()).toDouble() / sd.multiplier);
    ui->spinBoxMktPerc->setValue(record.value(_futfutParams->_marketPercentage->getParamName()).toInt());
    ui->checkBoxIsTbt->setChecked(record.value(_futfutParams->_isTbt->getParamName()).toBool());
    int index = ui->comboBoxHedgeMethod->findText(record.value(_futfutParams->_hedgeMethod->getParamName()).toString());
    index = index == -1 ? 0 : index;
    ui->comboBoxHedgeMethod->setCurrentIndex(index);

}

/**
*  recieve custom response from server. It extract that data , and stored into the database.
*
* @brief recieveCustomResponse
*
* @param apiCustomResponse

**/
void UiLibrary :: receiveCustomResponse(API2::API2_CustomResponse &apiCustomResponse)
{

    std::list<std::string> dataList = apiCustomResponse.getUiDataPair();
    QStringList keyValueList;
    QString key;
    long long value;

    int row = getBaseWrapper()->getStrategyRowFromAdminTokenId(apiCustomResponse.getAdminTokenId());
    if(row == -1) return;

    const API2:: SymbolDetail &sd = getBaseWrapper()->getSymbolIdDetail(_baseTableModel->item(row,_futfutParams->_symbolId->getColumnIndex())->text().toLongLong());
    bool oldState = _baseTableModel->blockSignals(true);

    foreach(const std::string& response, dataList)
    {
        keyValueList = QString::fromStdString(response).split(":"); //List of key and value.
        if(keyValueList.size() == 2)
        {
            key = keyValueList.at(0);
            value = keyValueList.at(1).toLongLong();
        }
        else
        {
            continue;
        }
        if(key == CURRENT_SPREAD)
        {
            getBaseWrapper()->setTableData(row, _futfutParams->_currentSpread->getColumnIndex(),
                                           (double(value)/sd.multiplier));
        }
    }
    _baseTableModel->blockSignals(oldState);
    getBaseWrapper()->updateTableView();

}

/**
    update displayed data after every 800ms.

    @brief updateDataOnTimer
**/

void UiLibrary::updateDataOnTimer()
{
    bool  _isNewStrategyWriteMethod = getBaseWrapper()->configFileValue("NEW_STRATEGY_WRITE_METHOD");
    if(!_isNewStrategyWriteMethod)
    {
        while(!getBaseWrapper()->_responseQueue.isEmpty())
        {
            getBaseWrapper()->updateResponse(getBaseWrapper()->_responseQueue.dequeue());
            if(_updateCounter++ == 8)
            {
                _updateCounter = 0;
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
bool UiLibrary :: isPortfolioNamePresent()
{
    return false;
}

/**
  * if strategy leg param is present in startegy
  * @brief isStrategyLegPresent
  */
bool UiLibrary::isStrategyLegPresent()
{
    return false;
}

/**
    if total quantity allowed in strategy
    @brief isSidTotalQtyHandling
    @return : true :- is allowed.
              false :- if not allowed.
**/
bool UiLibrary :: isSidTotalQtyHandling()
{
    return false;
}

void UiLibrary :: getDllVersionString(QString &dllVersionString)
{
    dllVersionString = DLL_VERSION_STRING;
}

extern "C" __declspec(dllexport) void* createObject()
{
    UiLibrary *ptr = new UiLibrary();
    return (void *)ptr;
}
