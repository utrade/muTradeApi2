#ifndef INVOKINGAPISTRUCTS_H
#define INVOKINGAPISTRUCTS_H
namespace INVOKING
{
  struct SgResponse
  {  
    CREATE_FIELD( UNSIGNED_CHARACTER, ResponseType );
    CREATE_FIELD( UNSIGNED_CHARACTER, RiskStatus );
    CREATE_FIELD( UNSIGNED_CHARACTER, StrategyComment );
    CREATE_FIELD( UNSIGNED_INTEGER, ParentId );
    CREATE_FIELD( UNSIGNED_INTEGER, Id );
  };
  struct TwoLegArbitrage
  {
    CREATE_FIELD(API2::AccountDetail, FirstLegAccountDetails);
    CREATE_FIELD(API2::AccountDetail, SecondLegAccountDetails);
    
    CREATE_FIELD( UNSIGNED_SHORT, TransactionType );
    CREATE_FIELD( UNSIGNED_LONG, SymbolIdFirstLeg );
    CREATE_FIELD( UNSIGNED_LONG, SymbolIdSecondLeg );
    CREATE_FIELD( UNSIGNED_LONG, QuantityFirstLeg );
    CREATE_FIELD( UNSIGNED_LONG, QuantitySecondLeg );
    CREATE_FIELD( UNSIGNED_INTEGER, LotSize );
    CREATE_FIELD( UNSIGNED_SHORT, FirstLegMode );
    CREATE_FIELD( UNSIGNED_INTEGER, ClientId);
    CREATE_FIELD( UNSIGNED_INTEGER, ParentStrategyId );
    CREATE_FIELD( UNSIGNED_LONG, ThresholdQuantity_2 );
    CREATE_FIELD( SIGNED_LONG, BidDifference );
    CREATE_FIELD( UNSIGNED_INTEGER, OpTicks );
    CREATE_FIELD( UNSIGNED_LONG, SqOff );
    CREATE_FIELD( UNSIGNED_LONG, MarketOrderPercent );
    CREATE_FIELD( SIGNED_LONG, PriceDifference );
    CREATE_FIELD(UNSIGNED_CHARACTER,SpreadType);  //default set to try
    CREATE_FIELD( UNSIGNED_INTEGER, TimerFirstLeg ); // default set to 1
    CREATE_FIELD( UNSIGNED_INTEGER, TimerSecondLeg ); // default set to 1



    public :
    
    TwoLegArbitrage();
   
    /*@brief getString provides dump for all inputed parameters of TwoLegArbitrage   
     */
    std::string getString();
  
  };
}
#endif
