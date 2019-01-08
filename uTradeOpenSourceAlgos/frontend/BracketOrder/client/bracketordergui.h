#ifndef BRACKETORDERGUI_H
#define BRACKETORDERGUI_H
#include "bracketorderparams.h"
#include <qglobal.h>
#include "../../../FrontEnd_Api_Includes/dll_includes/baseStrategyWrapper.h"
#include "../../../api2/api_includes/api2UserCommands.h"

#if IS_QT4_VERSION
#include <QDialog>
#else
#include <QtWidgets/QDialog>
#endif


namespace Ui {
class BracketOrderGui;
}

class BracketOrderGui : public APIWrapper
{
    Q_OBJECT
    BracketOrderParams *_bracketorderparams;
    QStandardItemModel *_baseTableModal;
    QHash<qlonglong,QVector<qlonglong> *> _portfolioIdTradedQtyHash;

    API2::StrategyParamMap *_paramsMap;
    QHash<qlonglong,qlonglong > _pidSidQty;


public:
    qlonglong quantity;
    qlonglong _refrencePrice;
    enum segment_Type
    {
        SEGMENT_TYPE_DEFAULT=0,
        SEGMENT_TYPE_CASH,
        SEGMENT_TYPE_FUTURE,
        SEGMENT_TYPE_BOTH,
        SEGMENT_TYPE_MAX=4

    };
    enum order_Mode
    {
        order_Mode_BUY,
        order_Mode_SELL,
        order_Mode_MAX
    };
    enum order_Type
    {
        order_Type_LIMIT,
        order_Type_MARKET,
        order_Type_MAX
    };
    enum fill_Type
    {
        fill_Type_DAY,
        fill_Type_IOC,
        fill_Type_MAX
    };
    enum quantity_Type
    {
        quantity_Type_Half,
        quantity_Type_Full,
        quantity_Type_Max
    };
    explicit BracketOrderGui(QWidget *parent = 0);
    bool isStrategyLegPresent();
    ~BracketOrderGui();

private:
    Ui::BracketOrderGui *ui;
    bool _isSorEnable;
    bool _isNewStrategyWriteMethod;
    QTimer _timer;
    int _updateCounter;
    //static BracketOrderGui *_bracketOrderGui;

    void initialize();
    void populateElements();
    void setDefaultIndex();
    void initializeSymbolPanel();
    void populateStrategyParams();
    QString getOrderTypeStr(const int &orderType);
    QString getFillTpyeStr(unsigned short orderValidity);
    QString getQuantityType(const int &quantityType);
    void getDllVersionString(QString &dllVersionString);
    void initDisplay();

    bool validateData(API2::PORTFOLIO_STATE state);
    void updateSymbolIdsDetail(int row, bool isUpdateAll);
    bool buildCommandFromUi(API2::PORTFOLIO_STATE state);
    bool isSpreadCalculationAllowed();
    void updateRemainingFeilds(int row, QSqlRecord &adminTokenIdData);
    void setApiCommand(API2::UserParams *apiParams, QSqlRecord &record, int stgCount, short type);
    bool isPortfolioNamePresent();
    bool isSidTotalQtyHandling();
    void receiveStrategyResponse(API2::Strategy &strategyResponse);
    void populateUIPanels(int row, QSqlRecord &record, bool isNewState);
    void updateEditableFieldColor(int row, QColor color);
    void setBasePointer(BaseStrategyWrapper *ptr)
    {
        setBaseWrapper(ptr);

    }
    void initializeTabOrder();
    short getOrderMode(const QString & orderMode);
    void setPortfolioDefaultValues(QStringList &portfolioRow);
    bool isNewState();
    void setConnections();


private slots:
    void setPrecisionDecimal();
    void isOrderTypeChanged();
    void updateDataOnTimer();
    void onCtrlSpacePressed();
    void onEscapePressed();
    void onUpKeyPressed();
    void OnDownKeyPressed();
    void onClosePushButtonClicked();
    void onStopPushButtonClicked();
    void onAddPushButtonClicked();
    void onNewPushButtonClicked();
    void onEditPushButtonClicked();
    void onCommitPushButtonClicked();
    void onRemovePushButtonClicked();
    void onStopAllPushButtonclicked();
    void onRunPushButtonClicked();
    void onAltSPressed();
    void onAltOPressed();
    void onRemoveAllClicked();

};

#endif // BRACKETORDERGUI_H
