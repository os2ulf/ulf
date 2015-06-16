<?php
/**
 * @file
 * Template for a 2 column panel layout.
 *
 * This template provides a two column panel display layout, with
 * each column roughly equal in width.
 *
 * Variables:
 * - $id: An optional CSS id to use for the layout.
 * - $content: An array of content, each item in the array is keyed to one
 *   panel of the layout. This layout supports the following sections:
 *   - $content['left']: Content in the left column.
 *   - $content['right']: Content in the right column.
 */
?>
<div class="layout--middle-split">
  <div class="layout-inner">
    <div class="layout-element-alpha">
      <div class="layout-element-inner"><?php print $content['left']; ?></div>
    </div>

    <div class="layout-element-beta">
      <div class="layout-element-inner"><?php print $content['right']; ?></div>
    </div>
  </div>
</div>
