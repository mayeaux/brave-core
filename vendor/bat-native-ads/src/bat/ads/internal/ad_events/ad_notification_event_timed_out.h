/* Copyright (c) 2019 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BAT_ADS_INTERNAL_AD_EVENTS_AD_EVENT_TIMED_OUT_H_
#define BAT_ADS_INTERNAL_AD_EVENTS_AD_EVENT_TIMED_OUT_H_

#include "bat/ads/internal/ad_events/ad_event.h"
#include "bat/ads/internal/ads_impl.h"
#include "bat/ads/notification_info.h"

namespace ads {

class AdNotificationEventTimedOut : public AdEvent<NotificationInfo> {
 public:
  AdNotificationEventTimedOut(
      AdsImpl* ads);

  ~AdNotificationEventTimedOut() override;

  void Trigger(
      const NotificationInfo& info) override;

 private:
  AdsImpl* ads_;  // NOT OWNED
};

}  // namespace ads

#endif  // BAT_ADS_INTERNAL_AD_EVENTS_AD_EVENT_TIMED_OUT_H_