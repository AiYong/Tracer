#include "AccountTrackerSetting.h"

#include "Account.h"
#include "Position.h"
#include "Instrument.h"

AccountTrackSettings::AccountTrackSettings(
        Account *pTradeAccount,
        Account *pTrackAccount,
        double dMaxMargin
        )
    :m_pTradeAccount(pTrackAccount),
     m_pTrackAccount(pTrackAccount),
     m_dMaxMargin(dMaxMargin)
{

}

AccountTrackSettings::~AccountTrackSettings()
{

}



Account* AccountTrackSettings::GetTradeAccount() const
{
    return m_pTradeAccount;
}


Account* AccountTrackSettings::GetTrackAccount() const
{
    return m_pTrackAccount;
}


double AccountTrackSettings::GetMaxMargin() const
{
    return m_dMaxMargin;
}


double AccountTrackSettings::GetAvailableMargin() const
{
  double dAvailableMargin = m_dMaxMargin;
  for(int nCount = 0 ; nCount < m_lInstrument.size() ; nCount++)
  {
      Instrument *pCurInstrument = m_lInstrument[count];
      QList<Position*> &lPosition = m_mPositions[pCurInstrument];
      for(int nPositionCount = 0 ; nPositionCount < lPosition.size() ; nPositionCount++)
      {
          Position *pPosition = lPosition[nPositionCount];
          dAvailableMargin = dAvailableMargin - pPosition->GetDynamicMargin();
      }
  }
  return dAvailableMargin;
}


void AccountTrackSettings::AddInstrument(Instrument *pInstrument)
{
    m_lInstrument.append(pInstrument);
}


void AccountTrackSettings::RemoveInstrument(Instrument *pInstrument)
{
    m_lInstrument.removeAll(pInstrument);
}

QList<Instrument*> AccountTrackSettings::GetInstruments() const
{
    return m_lInstrument;
}


void AccountTrackSettings::AddPosition(Instrument *pInstrument,Position *pPosition)
{
    m_mPositions[pInstrument].append(pPosition);
}

void AccountTrackSettings::RemovePosiiton(Instrument *pInstrument,Position *pPosition)
{
    m_mPositions[pInstrument].removeAll(pPosition);
}

QList<Position*> const& AccountTrackSettings::GetPositions(Instrument *pInstrument)
{
    return m_mPositions[pInstrument];
}

QMap<Instrument*,QList<Position*>> const& AccountTrackSettings::GetPositions() const
{
    return m_mPositions;
}

QList<Order*> const& AccountTrackSettings::GetOrders(Instrument *pInstrument)
{
    return m_mOrders[pInstrument];
}

QMap<Instrument*,QList<Order*>> const& AccountTrackSettings::GetOrders() const
{
    return m_mOrders;
}

bool AccountTrackSettings::NeedTrack(Instrument *pInstrument) const
{
    for(int count = 0 ; count < m_lInstrument.size() ; count++)
    {
        Instrument *pCurInstrument = m_lInstrument[count];
        if(pCurInstrument->GetName() == pInstrument->GetName())
        {
            return false;
        }
    }
    return true;
}
