/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

import * as React from 'react'

// DND utils
import { SortableContainer, SortableContainerProps } from 'react-sortable-hoc'

// Feature-specific components
import { ListWidget as List } from '../../components/default/topSites'

// Types
import { WidgetProps } from '../../components/default/widget'

// Component group
import TopSiteTile from './topSiteTile'
import { isTopSitePinned } from '../../helpers/newTabUtils'

interface Props {
  gridSites: NewTab.Site[]
  actions: any
  blockNumber: number
  textDirection: string
  showWidget: boolean
  menuPosition: 'left' | 'right'
  hideWidget: () => void
}

class TopSitesList extends React.PureComponent<Props, {}> {
  render () {
    const {
      actions,
      gridSites,
      blockNumber,
      textDirection,
      showWidget,
      menuPosition,
      hideWidget
    } = this.props
    return (
      <>
        <List
          blockNumber={blockNumber}
          textDirection={textDirection}
          showWidget={showWidget}
          menuPosition={menuPosition}
          hideWidget={hideWidget}
        >
          {gridSites.map((site: NewTab.Site, index: number) => (
            <TopSiteTile
              key={site.id}
              actions={actions}
              index={index}
              siteData={site}
              // do not allow sorting pinned items
              disabled={isTopSitePinned(site)}
            />
          ))}
        </List>
      </>
    )
  }
}

type DynamicListProps = SortableContainerProps & WidgetProps & Props
export default SortableContainer(
  (props: DynamicListProps) => <TopSitesList {...props} />
)
