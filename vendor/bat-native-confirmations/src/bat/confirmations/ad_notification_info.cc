/* Copyright (c) 2019 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "bat/confirmations/ad_notification_info.h"

namespace confirmations {

AdNotificationInfo::AdNotificationInfo() :
    type(ConfirmationType::kUnknown) {
}

AdNotificationInfo::AdNotificationInfo(
    const AdNotificationInfo& info)
    : id(info.id),
      creative_set_id(info.creative_set_id),
      category(info.category),
      advertiser(info.advertiser),
      text(info.text),
      url(info.url),
      uuid(info.uuid),
      type(info.type) {
}

AdNotificationInfo::~AdNotificationInfo() = default;

}  // namespace confirmations
