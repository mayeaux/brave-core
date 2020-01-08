/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

import { types } from '../../../brave_new_tab_ui/constants/new_tab_types'
import { Stats } from '../../../brave_new_tab_ui/api/stats'
import { Preferences } from '../../../brave_new_tab_ui/api/preferences'
import * as actions from '../../../brave_new_tab_ui/actions/new_tab_actions'

describe('newTabActions', () => {
  // TODO(petemill): We possibly don't need a test for every action to
  //   just to check that the actions are passing their payloads correctly.
  //   These aren't valid tests to make sure the reducer expects what it gets
  //   since we can change the payload signature here and in the actions,
  //   and still get an error in the reducer. It's perhaps more useful to get
  //   a build time error by using Typescript types in the reducer for each
  //   action payload.
  //   https://redux.js.org/recipes/usage-with-typescript
  it('statsUpdated', () => {
    const stats: Stats = {
      adsBlockedStat: 1,
      fingerprintingBlockedStat: 2,
      httpsUpgradesStat: 3,
      javascriptBlockedStat: 4,
      trackersBlockedStat: 5
    }
    expect(actions.statsUpdated(stats)).toEqual({
      meta: undefined,
      payload: {
        stats
      },
      type: types.NEW_TAB_STATS_UPDATED
    })
  })
  it('preferencesUpdated', () => {
    const preferences: Preferences = {
      showBackgroundImage: false,
      showStats: false,
      showClock: false,
      showTopSites: false
    }
    expect(actions.preferencesUpdated(preferences)).toEqual({
      meta: undefined,
      type: types.NEW_TAB_PREFERENCES_UPDATED,
      payload: preferences
    })
  })
})
