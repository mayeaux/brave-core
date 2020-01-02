/* Copyright (c) 2019 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "bat/confirmations/publisher_ad_info.h"

namespace confirmations {

PublisherAdInfo::PublisherAdInfo()
    : type(ConfirmationType::kUnknown) {
}

PublisherAdInfo::PublisherAdInfo(
    const PublisherAdInfo& info)
    : id(info.id),
      creative_set_id(info.creative_set_id),
      category(info.category),
      size(info.size),
      creative_url(info.creative_url),
      target_url(info.target_url),
      uuid(info.uuid),
      type(info.type) {
}

PublisherAdInfo::~PublisherAdInfo() = default;

}  // namespace confirmations
