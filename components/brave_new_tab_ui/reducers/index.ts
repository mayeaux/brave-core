/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

import { combineReducers } from 'redux'

// Reducers
import newTabReducer from './new_tab_reducer'
import topSitesReducer from './top_sites_reducer'

export default combineReducers<NewTab.ApplicationState>({
  newTabData: newTabReducer,
  topSitesData: topSitesReducer
})
