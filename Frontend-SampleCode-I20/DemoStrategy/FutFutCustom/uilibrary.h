#ifndef UILIBRARY_H
#define UILIBRARY_H

#include <QDialog>
#include "futfutparams.h"
#include "../includes/dll_includes/baseStrategyWrapper.h"
#include "../includes/dll_includes/StrategyConstants.h"

#define fileName "uTrade"

namespace Ui {
class UiLibrary;
}

class UiLibrary : public APIWrapper
{
    Q_OBJECT

public:
    explicit UiLibrary(QWidget *parent = 0);
    ~UiLibrary();

    void setBasePointer(BaseStrategyWrapper *ptr)
    {
        setBaseWrapper(ptr);
    }

    void initDisplay();
    bool updateStrategyDefaultValues()
    {
        return true;
    }

private:
    Ui::UiLibrary *ui;
    FutFutParams *_futfutParams;
    QStandardItemModel *_baseTableModel;
    QTimer _timer;
    bool _isNewStrategyWriteMethod;
    int _updateCounter;
    API2::StrategyParamMap *_paramsMap;
    void initialize();
    void initializeSymbolPanel();
    void initializeFilter();
    void setDefaultIndex();

    //Flags
    bool isSpreadCalculationAllowed();
    bool isPortfolioNamePresent();
    bool isStrategyLegPresent();

    bool buildCommandFromUi(API2::PORTFOLIO_STATE state);
    void updateRemainingFeilds(int row, QSqlRecord &adminTokenIdData);
    void updateSymbolIdsDetail(int row, bool isUpdateAll);
    void populateUIPanels(int row, QSqlRecord &record, bool isNew);
    void setApiCommand(API2::UserParams * sampleCommand, QSqlRecord &record, int stgCount, short type);
    void receiveCustomResponse(API2::API2_CustomResponse &apiCustomResponse);
    bool validateData(API2::PORTFOLIO_STATE state);
    bool isSidTotalQtyHandling();
    void setPortfolioDefaultValues(QStringList &portfolioRow);
    void getDllVersionString(QString &dllVersionString);

public slots:
    //Overridden Slots
    void onNewPushButtonClicked();
    void onAddPushButtonClicked();
    void onRemovePushButtonClicked();
    void onEditPushButtonClicked();
    void onCommitPushButtonClicked();
    void onRunPushButtonClicked();
    void onAltMPressed();
    void onEscapePressed();
    void onRunActivated(){}
    void onCtrlSpacePressed();
    void onUpKeyPressed();
    void OnDownKeyPressed(){}
    void receiveStrategyResponse(API2::Strategy &strategyResponse);
    void updateDataOnTimer();
    void firstLegSymbolChanged();
};

#endif // UILIBRARY_H

