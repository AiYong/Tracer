#ifndef _TRACKER_POSITIONCOST_H_
#define _TRACKER_POSITIONCOST_H_

#include <QObject>

class Account;
class Instrument;

/**
 * @brief 手续费收取模式
 */
enum CommissionMode
{
    cmRatio,//比例
    cmDirect//直接收取
};

/**
 * @brief 保证金收取模式
 */
enum MarginMode
{
    mmRatio,//比例
    mmDirect//直接收取
};

/**
 * @brief 持仓成本
 */
class PositionCost
{
public:

    /**
     * @brief PositionCost
     * @param pInstrument
     * @param eCommissionMode
     * @param dLongOpenCommission
     * @param dShortOpenCommission
     * @param dLongCloseCommission
     * @param dShortCloseCommission
     * @param eMarginMode
     * @param dLongMargin
     * @param dShortMargin
     */
    PositionCost(
              Account *pAccount,
              Instrument *pInstrument,
              CommissionMode eCommissionMode,
              double dLongOpenCommission,
              double dShortOpenCommission,
              double dLongCloseCommission,
              double dShortCloseCommission,
              MarginMode eMarginMode,
              double dLongMargin,
              double dShortMargin
            );

public:

    Account* GetAccount() const;

    /**
     * @brief GetInstrument
     * @return
     */
    Instrument* GetInstrument() const;

    /**
     * @brief 返回手续费收取模式
     * @return
     */
    CommissionMode GetCommissionMode() const;

    /**
     * @brief 返回多开手续费
     * @return
     */
    double GetLongOpenCommission() const;

    /**
     * @brief 返回空开手续费
     * @return
     */
    double GetShortOpenCommission() const;

    /**
     * @brief 返回多平手续费
     * @return
     */
    double GetLongCloseCommission() const;

    /**
     * @brief 返回空平手续费
     * @return
     */
    double GetShortCloseCommission() const;

    /**
     * @brief 返回保证金收取模式
     * @return
     */
    MarginMode GetMarginMode() const;

    /**
     * @brief 返回多头保证金
     * @return
     */
    double GetLongMargin() const;

    /**
     * @brief 返回空头保证金
     * @return
     */
    double GetShortMargin() const;

private:

    Account *m_pAccount;
    Instrument *m_pInstrument;
    CommissionMode m_eCommissionMode;
    double m_dLongOpenCommission;
    double m_dShortOpenCommission;
    double m_dLongCloseCommission;
    double m_dShortCloseCommission;
    MarginMode m_eMarginMode;
    double m_dLongMargin;
    double m_dShortMargin;

};

#endif // _TRACKER_POSITIONCOST_H_
