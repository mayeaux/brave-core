/* Copyright (c) 2019 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "bat/ads/internal/reports.h"
#include "bat/ads/internal/time.h"
#include "bat/ads/internal/ads_impl.h"
#include "bat/ads/notification_info.h"
#include "bat/ads/publisher_ad_info.h"

#include "rapidjson/document.h"
#include "rapidjson/error/en.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"

namespace ads {

Reports::Reports(
    AdsImpl* ads)
    : is_first_run_(true),
      ads_(ads) {
}

Reports::~Reports() = default;

std::string Reports::GenerateAdNotificationEventReport(
    const NotificationInfo& info,
    const AdEventType event_type) {
  rapidjson::StringBuffer buffer;
  rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);

  if (is_first_run_) {
    is_first_run_ = false;

    writer.StartObject();

    writer.String("data");
    writer.StartObject();

    writer.String("type");
    writer.String("restart");

    writer.String("stamp");
    auto time_stamp = Time::Timestamp();
    writer.String(time_stamp.c_str());

    writer.EndObject();

    writer.EndObject();
  }

  writer.StartObject();

  writer.String("data");
  writer.StartObject();

  writer.String("type");
  writer.String("notify");

  writer.String("stamp");
  auto time_stamp = Time::Timestamp();
  writer.String(time_stamp.c_str());

  writer.String("eventType");
  switch (event_type) {
    case AdEventType::kViewed: {
      writer.String("generated");
      break;
    }

    case AdEventType::kClicked: {
      writer.String("clicked");
      break;
    }

    case AdEventType::kDismissed: {
      writer.String("dismissed");
      break;
    }

    case AdEventType::kTimedOut: {
      writer.String("timed out");
      break;
    }
  }

  writer.String("Classifications");
  writer.StartArray();
  auto classifications =
      helper::Classification::GetClassifications(info.category);
  for (const auto& classification : classifications) {
    writer.String(classification.c_str());
  }
  writer.EndArray();

  writer.String("adCatalog");
  if (ads_->IsCreativeSetFromSampleCatalog(info.creative_set_id)) {
    writer.String("sample-catalog");
  } else {
    writer.String(info.creative_set_id.c_str());
  }

  writer.String("targetUrl");
  writer.String(info.url.c_str());

  writer.EndObject();

  writer.EndObject();

  return buffer.GetString();
}

std::string Reports::GeneratePublisherAdEventReport(
    const PublisherAdInfo& info,
    const AdEventType event_type) {
  rapidjson::StringBuffer buffer;
  rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);

  if (is_first_run_) {
    is_first_run_ = false;

    writer.StartObject();

    writer.String("data");
    writer.StartObject();

    writer.String("type");
    writer.String("restart");

    writer.String("stamp");
    auto time_stamp = Time::Timestamp();
    writer.String(time_stamp.c_str());

    writer.EndObject();

    writer.EndObject();
  }

  writer.StartObject();

  writer.String("data");
  writer.StartObject();

  writer.String("type");
  writer.String("notify");

  writer.String("stamp");
  auto time_stamp = Time::Timestamp();
  writer.String(time_stamp.c_str());

  writer.String("eventType");
  switch (event_type) {
    case AdEventType::kViewed: {
      writer.String("generated");
      break;
    }

    case AdEventType::kClicked: {
      writer.String("clicked");
      break;
    }

    case AdEventType::kDismissed: {
      writer.String("dismissed");
      break;
    }

    case AdEventType::kTimedOut: {
      writer.String("timed out");
      break;
    }
  }

  writer.String("Classifications");
  writer.StartArray();
  auto classifications =
      helper::Classification::GetClassifications(info.category);
  for (const auto& classification : classifications) {
    writer.String(classification.c_str());
  }
  writer.EndArray();

  writer.String("adCatalog");
  if (ads_->IsCreativeSetFromSampleCatalog(info.creative_set_id)) {
    writer.String("sample-catalog");
  } else {
    writer.String(info.creative_set_id.c_str());
  }

  writer.String("targetUrl");
  writer.String(info.target_url.c_str());

  writer.EndObject();

  writer.EndObject();

  return buffer.GetString();
}

std::string Reports::GenerateConfirmationEventReport(
    const std::string& uuid,
    const ConfirmationType& type) const {
  rapidjson::StringBuffer buffer;
  rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);

  writer.StartObject();

  writer.String("data");
  writer.StartObject();

  writer.String("type");
  writer.String("confirmation");

  writer.String("stamp");
  auto time_stamp = Time::Timestamp();
  writer.String(time_stamp.c_str());

  writer.String("notificationId");
  writer.String(uuid.c_str());

  writer.String("notificationType");
  auto confirmation_type = std::string(type);
  writer.String(confirmation_type.c_str());

  writer.EndObject();

  writer.EndObject();

  return buffer.GetString();
}

std::string Reports::GenerateLoadEventReport(
    const LoadInfo& info) const {
  rapidjson::StringBuffer buffer;
  rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);

  writer.StartObject();

  writer.String("data");
  writer.StartObject();

  writer.String("type");
  writer.String("load");

  writer.String("stamp");
  auto time_stamp = Time::Timestamp();
  writer.String(time_stamp.c_str());

  writer.String("tabId");
  writer.Int(info.tab_id);

  writer.String("tabType");
  if (ads_->get_client()->GetSearchState()) {
    writer.String("search");
  } else {
    writer.String("click");
  }

  writer.String("tabUrl");
  writer.String(info.tab_url.c_str());

  writer.String("tabClassification");
  writer.StartArray();
  auto classifications =
      helper::Classification::GetClassifications(info.tab_classification);
  for (const auto& classification : classifications) {
    writer.String(classification.c_str());
  }
  writer.EndArray();

  auto page_score_cache = ads_->GetPageScoreCache();
  auto cached_page_score = page_score_cache.find(info.tab_url);
  if (cached_page_score != page_score_cache.end()) {
    writer.String("pageScore");
    writer.StartArray();
    for (const auto& page_score : cached_page_score->second) {
      writer.Double(page_score);
    }
    writer.EndArray();
  }

  writer.EndObject();

  writer.EndObject();

  return buffer.GetString();
}

std::string Reports::GenerateBackgroundEventReport() const {
  rapidjson::StringBuffer buffer;
  rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);

  writer.StartObject();

  writer.String("data");
  writer.StartObject();

  writer.String("type");
  writer.String("background");

  writer.String("stamp");
  auto time_stamp = Time::Timestamp();
  writer.String(time_stamp.c_str());

  writer.EndObject();

  writer.EndObject();

  return buffer.GetString();
}

std::string Reports::GenerateForegroundEventReport() const {
  rapidjson::StringBuffer buffer;
  rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);

  writer.StartObject();

  writer.String("data");
  writer.StartObject();

  writer.String("type");
  writer.String("foreground");

  writer.String("stamp");
  auto time_stamp = Time::Timestamp();
  writer.String(time_stamp.c_str());

  writer.EndObject();

  writer.EndObject();

  return buffer.GetString();
}

std::string Reports::GenerateBlurEventReport(
    const BlurInfo& info) const {
  rapidjson::StringBuffer buffer;
  rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);

  writer.StartObject();

  writer.String("data");
  writer.StartObject();

  writer.String("type");
  writer.String("blur");

  writer.String("stamp");
  auto time_stamp = Time::Timestamp();
  writer.String(time_stamp.c_str());

  writer.String("tabId");
  writer.Int(info.tab_id);

  writer.EndObject();

  writer.EndObject();

  return buffer.GetString();
}

std::string Reports::GenerateDestroyEventReport(
    const DestroyInfo& info) const {
  rapidjson::StringBuffer buffer;
  rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);

  writer.StartObject();

  writer.String("data");
  writer.StartObject();

  writer.String("type");
  writer.String("destroy");

  writer.String("stamp");
  auto time_stamp = Time::Timestamp();
  writer.String(time_stamp.c_str());

  writer.String("tabId");
  writer.Int(info.tab_id);

  writer.EndObject();

  writer.EndObject();

  return buffer.GetString();
}

std::string Reports::GenerateFocusEventReport(
    const FocusInfo& info) const {
  rapidjson::StringBuffer buffer;
  rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);

  writer.StartObject();

  writer.String("data");
  writer.StartObject();

  writer.String("type");
  writer.String("focus");

  writer.String("stamp");
  auto time_stamp = Time::Timestamp();
  writer.String(time_stamp.c_str());

  writer.String("tabId");
  writer.Int(info.tab_id);

  writer.EndObject();

  writer.EndObject();

  return buffer.GetString();
}

std::string Reports::GenerateSettingsEventReport() const {
  DCHECK(ads_);
  if (!ads_) {
    return "Failed to generate settings event report";
  }

  rapidjson::StringBuffer buffer;
  rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);

  writer.StartObject();

  writer.String("data");
  writer.StartObject();

  writer.String("type");
  writer.String("settings");

  writer.String("stamp");
  auto time_stamp = Time::Timestamp();
  writer.String(time_stamp.c_str());

  writer.String("settings");
  writer.StartObject();

  writer.String("locale");
  auto locale = ads_->get_ads_client()->GetLocale();
  writer.String(locale.c_str());

  writer.String("notifications");
  writer.StartObject();

  writer.String("shouldShow");
  auto should_show = ads_->get_ads_client()->ShouldShowNotifications();
  writer.Bool(should_show);

  writer.EndObject();

  writer.String("userModelLanguage");
  auto user_model_language = ads_->get_client()->GetUserModelLanguage();
  writer.String(user_model_language.c_str());

  writer.String("adsPerDay");
  auto ads_per_day = ads_->get_ads_client()->GetAdsPerDay();
  writer.Uint64(ads_per_day);

  writer.String("adsPerHour");
  auto ads_per_hour = ads_->get_ads_client()->GetAdsPerHour();
  writer.Uint64(ads_per_hour);

  writer.EndObject();

  writer.EndObject();

  writer.EndObject();

  return buffer.GetString();
}

}  // namespace ads