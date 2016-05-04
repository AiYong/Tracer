#ifndef _TRACKER_ORDERSTATUS_H_
#define _TRACKER_ORDERSTATUS_H_

/**
 * @brief 报单状态
 */
enum OrderStatus
{
    osNew,
    osSubmitted,
    osQueued,
    osPartedTraded,
    osCompletedTraded,
    osCancelling,
    osCancelled,
    osCancelledAndPartedTraded
};

#endif // _TRACKER_ORDERSTATUS_H_
