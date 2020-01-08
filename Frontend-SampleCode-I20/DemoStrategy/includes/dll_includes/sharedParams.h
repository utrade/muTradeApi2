#ifndef SHAREDPARAMS_H
#define SHAREDPARAMS_H

#include "sharedEnums.h"
#include <QtWidgets>
namespace API2
{

class StrategyParameters
{

private :
    QLabel  *_uiLabel;
    QWidget *_uiWidget;

    short _uiElementType;
    short _uiElementState;
    short _elementDataType;
    short _updatable;
    short _isDbField;

    QString _uiLabelName;
    QVariant _tempValue;
    QVariant _uiValue;

    int _columnIndex;
    short _filterType;
    short _isShowInTable;
    short _isColumnHidden;
    bool _isDefaultPrecision;
    QString _columnName;
    bool _isColumnEditable;
    short _sortingType;
    bool _isShowInPortfolio;
    short _portfolioIndex;
    bool _isColumnCheckable;

public:

    /**
    *@brief Constructor structure
    *    name - DbName
    *    colName
    *    widget
    *    widgetype
    *    datatype string
    *    state  enable
    *    tablestatus
    *    dbstatus
    *    isUpdatable
    **/
    StrategyParameters(const QString &paramNameArg,
                       const QString &colName,
                       QWidget *uiWidget,
                       short elementType,
                       short dataType=API2::DATA_TYPE_UNSIGNED_LONG,
                       short state=API2::UI_STATE_DISABLED,
                       short showTableStatus =API2::TABLE_STATE_HIDE,
                       short isDbColumn = API2::DB_FEILD_HIDE,
                       short isUpdatable = API2::UPDATE_STATE_DISABLE,
                       short portfolioState = API2::SHOW_IN_PORTFOLIO_DISABLE)
        : _uiWidget(uiWidget),
          _uiElementState(state),
          _isShowInTable(showTableStatus),
          _uiElementType(elementType),
          _elementDataType(dataType),
          _uiLabelName(paramNameArg),
          _columnName(colName),
          _isDbField(isDbColumn),
          _updatable(isUpdatable),
          _isColumnEditable(false),
          _isColumnHidden(false),
          _isDefaultPrecision(true),
          _isColumnCheckable(false)
    {
        _isShowInPortfolio = (portfolioState == API2::SHOW_IN_PORTFOLIO_ENABLE) && _isDbField ;
        _uiLabel = new QLabel(paramNameArg);
        _filterType = WidgetType_MAX;
        _sortingType = SortingType_MAX;
        _uiElementState = elementType==UI_ELEMENT_NO_UI ? false : _uiElementState;
        if(_uiWidget)
        {
            _uiWidget->setEnabled(_uiElementState);
            _tempValue=getParamUIValue();
        }
        else
            _tempValue = 0;
    }


    ~StrategyParameters()
    {

    }

    void setVisible(bool isVisible)
    {
        _uiWidget->setVisible(isVisible);
        _uiLabel->setVisible(isVisible);
    }


    QVariant  getParamValue()
    {
        if(( _elementDataType==DATA_TYPE_INTEGER || _elementDataType==DATA_TYPE_SHORT)
                && (_uiElementType!=UI_ELEMENT_DOUBLE_SPIN_BOX))
        {
            if(_uiElementType == UI_ELEMENT_COMBO_BOX)
                _tempValue=_tempValue.toInt();
        }
        return _tempValue;
    }

    QVariant  getParamUIValue()
    {
        double value=0.00f;
        if(!_uiWidget) return _tempValue;
        switch(_uiElementType)
        {
        case UI_ELEMENT_LABEL :
            break;
        case UI_ELEMENT_COMBO_BOX:
            _uiValue =((QComboBox *)getElement())->currentText();
            break;
        case UI_ELEMENT_LINE_EDIT:
            _uiValue =((QLineEdit *)getElement())->text();
            break;
        case UI_ELEMENT_CHECK_BOX:
            _uiValue = ((QCheckBox *)_uiWidget)->isChecked();
            break;
        case UI_ELEMENT_PUSH_BUTTON:
            break;
        case UI_ELEMENT_SPIN_BOX:
        case UI_ELEMENT_SPIN_BOX_NON_QTY:
            _uiValue =((QSpinBox *)getElement())->value();
            break;
        case UI_ELEMENT_DOUBLE_SPIN_BOX:
            value =((QDoubleSpinBox *)_uiWidget)->value();
            _uiValue = QString::number(value,'f',((QDoubleSpinBox *)_uiWidget)->decimals()).remove(".").toLongLong();
            break;
        case UI_ELEMENT_RADIO_BUTTON:
            break;
        case UI_ELEMENT_NO_UI:
            _uiValue = 0;
            break;
        case UI_ELEMENT_SLIDER:
            return ((QSlider *)_uiWidget)->value();
            break;
        default:
            break;
        }

        if(( _elementDataType==DATA_TYPE_INTEGER || _elementDataType==DATA_TYPE_SHORT)
                && (_uiElementType!=UI_ELEMENT_DOUBLE_SPIN_BOX))
        {
            if(_uiElementType == UI_ELEMENT_COMBO_BOX)
                _uiValue.setValue(((QComboBox *)_uiWidget)->currentIndex());
        }

        return _uiValue;
    }

    QString getDoubleText()
    {
        if(_uiElementType == UI_ELEMENT_DOUBLE_SPIN_BOX)
        {
            double value =((QDoubleSpinBox *)_uiWidget)->value();
            return  QString::number(value,'f',((QDoubleSpinBox *)_uiWidget)->decimals());
        }
        return " ";
    }


    QVariant getValueFromDouble()
    {
        if(_uiElementType == UI_ELEMENT_DOUBLE_SPIN_BOX)
        {
            double value = _tempValue.toLongLong()/pow(10.0, ((QDoubleSpinBox *)_uiWidget)->decimals());
            return  QString::number(value,'f',((QDoubleSpinBox *)_uiWidget)->decimals());
        }
        return " ";
    }



    void  setValue(QVariant value)
    {
        _tempValue=value;
    }


    void  setUIValue(const QVariant &value)
    {
        _uiValue=value;
        if(_uiWidget)
        {
            switch(_uiElementType)
            {
            case UI_ELEMENT_LABEL :
                break;
            case UI_ELEMENT_COMBO_BOX:
            {
                QString typeName(value.typeName());
                switch(_elementDataType)
                {
                case DATA_TYPE_INTEGER:
                    ((QComboBox *)_uiWidget)->setCurrentIndex(value.toInt());
                    break;
                default:
                if(!typeName.compare("QString"))
                {
                    setCurrentIndex(findText(value.toString()));
                }
                }
            }
                break;
            case UI_ELEMENT_LINE_EDIT:
                ((QLineEdit *)_uiWidget)->setText(_uiValue.toString());
                break;
            case UI_ELEMENT_CHECK_BOX:
                ((QCheckBox *)_uiWidget)->setChecked(value.toBool());
                break;
            case UI_ELEMENT_PUSH_BUTTON:
                break;
            case UI_ELEMENT_SPIN_BOX:
            case UI_ELEMENT_SPIN_BOX_NON_QTY:
                ((QSpinBox *)_uiWidget)->setValue(_uiValue.toInt());
                break;
            case UI_ELEMENT_DOUBLE_SPIN_BOX:
                ((QDoubleSpinBox *)_uiWidget)->setValue(_uiValue.toDouble());
                break;
            case UI_ELEMENT_RADIO_BUTTON:
                break;
            case UI_ELEMENT_NO_UI:
                _uiValue=value;
                break;
            case UI_ELEMENT_SLIDER:
                ((QSlider *)_uiWidget)->setValue(_uiValue.toInt());
            default:
                break;
            }
            if(_elementDataType==DATA_TYPE_DOUBLE){_uiValue=value.toDouble();}
        }
    }

    void setEnabled(bool value)
    {
        if(_uiElementType!=UI_ELEMENT_NO_UI || _uiElementType!=UI_ELEMENT_CHECK_BOX)
        {
            if(_uiWidget)
                _uiWidget->setEnabled(value);
        }
    }

    void addItem(const QString str)
    {
        if(_uiElementType!=UI_ELEMENT_COMBO_BOX){return;}
        ((QComboBox *)_uiWidget)->addItem(str);
    }

    void setCurrentIndex(short index)
    {
        if(_uiElementType!=UI_ELEMENT_COMBO_BOX){return;}
        ((QComboBox *)_uiWidget)->setCurrentIndex(index);
    }

    short getCurrenIndexComboBox()
    {
        if(_uiElementType!=UI_ELEMENT_COMBO_BOX){return 0;}
        return(((QComboBox *)_uiWidget)->currentIndex());
    }

    int findText(const QString &str)
    {
        return(((QComboBox*)_uiWidget)->findText(str));
    }

    void clear()
    {
        QString str ="";
        switch(_uiElementType)
        {
        case UI_ELEMENT_LABEL :
            _uiValue.setValue(str);
            ((QLabel *)getElement())->clear();
            break;
        case UI_ELEMENT_COMBO_BOX:
            _uiValue.setValue(str);
            ((QComboBox *)getElement())->clear();
            break;
        case UI_ELEMENT_LINE_EDIT:
            _uiValue.setValue(str);
            ((QLineEdit *)getElement())->clear();
            break;
        case UI_ELEMENT_CHECK_BOX:
            _uiValue.setValue(false);
            ((QCheckBox *)_uiWidget)->setChecked(false);
            break;
        case UI_ELEMENT_PUSH_BUTTON:
            break;
        case UI_ELEMENT_SPIN_BOX:
        case UI_ELEMENT_SPIN_BOX_NON_QTY:
            _uiValue.setValue(0);
            ((QSpinBox *)getElement())->setValue(0);
            break;
        case UI_ELEMENT_DOUBLE_SPIN_BOX:
            _uiValue.setValue(0.00);
            ((QDoubleSpinBox *)getElement())->setValue(0.00);
            break;
        case UI_ELEMENT_RADIO_BUTTON:
            break;
        case UI_ELEMENT_NO_UI:
            break;
        case UI_ELEMENT_SLIDER:
            _uiValue.setValue(0);
            ((QSlider *)_uiWidget)->setValue(0);
        default:
            break;
        }
    }


    bool compareValue(QVariant toCompare)
    {
        switch(_elementDataType)
        {
        case  DATA_TYPE_SHORT:
            return(getParamValue().toInt()==toCompare.toInt());
        case  DATA_TYPE_INTEGER:
            return(getParamValue().toInt()==toCompare.toInt());
        case  DATA_TYPE_FLOAT:
            return(getParamValue().toFloat()==toCompare.toFloat());
        case  DATA_TYPE_DOUBLE:
            return(getParamValue().toDouble()==toCompare.toDouble());
        case  DATA_TYPE_STRING:
            return(getParamValue().toString()==toCompare.toString());
        case  DATA_TYPE_SIGNED_LONG:
            return(getParamValue().toLongLong()==toCompare.toLongLong());
        case  DATA_TYPE_UNSIGNED_LONG:
            return(getParamValue().toLongLong()==toCompare.toLongLong());
        case  DATA_TYPE_CHARACTER:
            return(getParamValue().toChar()==toCompare.toChar());
        case  DATA_TYPE_BOOLEAN:
            return(getParamValue().toBool()==toCompare.toBool());
        }
        return false;
    }

    void setcolumnProperties(QString colName,int colIndex,bool show)
    {
        _columnName=colName;
        _columnIndex=colIndex;
        _isShowInTable=show;
    }
    void setColumnEditable(bool type){_isColumnEditable = type;}
    bool isColumnEditable(){return _isColumnEditable;}
    bool isDbField(){return _isDbField;}
    bool isUpdatable(){return _updatable;}
    int getDecimals(){ return ((QDoubleSpinBox *)_uiWidget)->decimals();}
    QString ItemAt(int index){return ((QComboBox *)_uiWidget)->itemText(index);}
    void setColumnName(QString colName){_columnName=colName;}
    void setColumnIndex(int colIndex){_columnIndex=colIndex;}
    void showLabel(bool value){ _uiLabel->setVisible(value);}
    void setFilterType(short type){_filterType = type;}
    short getFilterType(){return _filterType;}
    void setWidget(QWidget *wid){_uiWidget = wid;}
    void setDefaultPrecision(bool isDefaultPrecision){_isDefaultPrecision =isDefaultPrecision;}
    bool isDefaultPrecision(){return  _isDefaultPrecision;}
    void setChecked(bool value){((QCheckBox *)_uiWidget)->setChecked(value);}
    void removeItem(int index) {((QComboBox *)_uiWidget)->removeItem(index);}
    QWidget* getElement()   {return _uiWidget;}
    QString getWidgetName() {return _uiLabel->text();}
    short getElementType(){return _uiElementType;}
    short isShowInStrategyTable(){return _isShowInTable;}
    short getElementDataType(){return _elementDataType;}
    bool isChecked(){return(((QCheckBox *)_uiWidget)->isChecked());}
    short getParamState(){return _uiElementState;}
    int Count(){ return ((QComboBox *)_uiWidget)->count();}
    bool isGui(){ return _uiElementType!=UI_ELEMENT_NO_UI;}
    Qt::CheckState checkedState(){return ((QCheckBox *)_uiWidget)->checkState();}
    qlonglong getLongLongValue(){ return getParamValue().toLongLong();}
    QString currentText(){return getParamValue().toString();}
    int currentIndex(){return(((QComboBox *)_uiWidget)->currentIndex());}
    int spinBoxValue(){ return  getParamValue().toInt();}
    double dspinBoxValue() {return getParamValue().toDouble();}
    QString getParamName(){ return _uiLabelName;}
    QString getColumnName(){ return _columnName;}
    int getColumnIndex(){return _columnIndex;}
    void setColumnHidden(bool isHidden){_isColumnHidden =isHidden;}
    bool isColumnHidden(){return  _isColumnHidden;}
    void setSortingType(short type){_sortingType = type;}
    short getSortingType(){return _sortingType;}
    void setPortfolioIndex(short index){_portfolioIndex = index;}
    short getPortfolioIndex(){return _portfolioIndex;}
    bool isShowInPortfolio() {return _isShowInPortfolio; }

    void setColumnCheckable(bool isCheckable)
    {
        _isColumnCheckable = isCheckable;
    }

    bool isColumnCheckable()
    {
        return _isColumnCheckable;
    }
};
typedef StrategyParameters PARAM;
typedef QMap<QString,PARAM *>  StrategyParamMap;
typedef QMap<QString,QVariant>  StgValueMap;
typedef QVector<StrategyParamMap *>   ParamMapGroup;
}
#endif // SHAREDPARAMS_H


