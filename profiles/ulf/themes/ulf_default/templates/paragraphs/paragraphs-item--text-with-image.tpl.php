<?php

/**
 * @file
 * Default theme implementation for a single paragraph item.
 *
 * Available variables:
 * - $content: An array of content items. Use render($content) to print them
 *   all, or print a subset such as render($content['field_example']). Use
 *   hide($content['field_example']) to temporarily suppress the printing of a
 *   given element.
 * - $classes: String of classes that can be used to style contextually through
 *   CSS. It can be manipulated through the variable $classes_array from
 *   preprocess functions. By default the following classes are available, where
 *   the parts enclosed by {} are replaced by the appropriate values:
 *   - entity
 *   - entity-paragraphs-item
 *   - paragraphs-item-{bundle}
 *
 * Other variables:
 * - $classes_array: Array of html class attribute values. It is flattened into
 *   a string within the variable $classes.
 *
 * @see template_preprocess()
 * @see template_preprocess_entity()
 * @see template_process()
 */
?>
<div class="<?php print $classes; ?>"<?php print $attributes; ?>>
  <?php
    if (isset($content['field_paragraph_image'])) {
      print render($content['field_paragraph_image']);
    }
  ?>
  <?php if (isset($content['field_paragraph_title']) || isset($content['field_paragraph_body'])) { ?>
    <div class="text__content<?php print isset($content['field_paragraph_image']) ? ' text__content--with-visuals' : ''; ?>">
      <?php print render($content['field_paragraph_title']); ?>
      <?php print render($content['field_paragraph_body']); ?>
      <?php if ($show_button): ?>
        <div class="text__cta">
          <?php print render($content['field_paragraph_button']) ?>
        </div>
      <?php endif; ?>
    </div>
  <?php } ?>
</div>
