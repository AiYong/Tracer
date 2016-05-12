#include "OrderProcessor.h"

OrderProcessor::OrderProcessor(Account const*pAccount)
    :m_pAccount(const_cast<Account*>(pAccount))
{

}

OrderProcessor::~OrderProcessor()
{

}
