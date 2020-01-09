/* Copyright (c) 2019 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "bat/ads/publisher_ad_info.h"
#include "bat/ads/confirmation_type.h"

#include "bat/ads/internal/json_helper.h"

#include "base/logging.h"

namespace ads {

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

const std::string PublisherAdInfo::ToJson() const {
  std::string json;
  SaveToJson(*this, &json);
  return json;
}

Result PublisherAdInfo::FromJson(
    const std::string& json,
    std::string* error_description) {
  rapidjson::Document document;
  document.Parse(json.c_str());

  if (document.HasParseError()) {
    if (error_description != nullptr) {
      *error_description = helper::JSON::GetLastError(&document);
    }

    return FAILED;
  }

  if (document.HasMember("id")) {
    id = document["id"].GetString();
  }

  if (document.HasMember("creative_set_id")) {
    creative_set_id = document["creative_set_id"].GetString();
  }

  if (document.HasMember("category")) {
    category = document["category"].GetString();
  }

  if (document.HasMember("size")) {
    size = document["size"].GetString();
  }

  if (document.HasMember("creative_url")) {
    creative_url = document["creative_url"].GetString();
  }

  if (document.HasMember("target_url")) {
    target_url = document["target_url"].GetString();
  }

  if (document.HasMember("uuid")) {
    uuid = document["uuid"].GetString();
  }

  if (document.HasMember("confirmation_type")) {
    std::string confirmation_type = document["confirmation_type"].GetString();
    type = ConfirmationType(confirmation_type);
  }

  return SUCCESS;
}

void SaveToJson(JsonWriter* writer, const PublisherAdInfo& info) {
  writer->StartObject();

  writer->String("id");
  writer->String(info.id.c_str());

  writer->String("creative_set_id");
  writer->String(info.creative_set_id.c_str());

  writer->String("category");
  writer->String(info.category.c_str());

  writer->String("size");
  writer->String(info.size.c_str());

  writer->String("creative_url");
  writer->String(info.creative_url.c_str());

  writer->String("target_url");
  writer->String(info.target_url.c_str());

  writer->String("uuid");
  writer->String(info.uuid.c_str());

  writer->String("confirmation_type");
  auto type = std::string(info.type);
  writer->String(type.c_str());

  writer->EndObject();
}

}  // namespace ads
