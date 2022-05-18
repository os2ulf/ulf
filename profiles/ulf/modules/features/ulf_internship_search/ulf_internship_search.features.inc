<?php

/**
 * @file
 * ulf_internship_search.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ulf_internship_search_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "page_manager" && $api == "pages_default") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_default_search_api_index().
 */
function ulf_internship_search_default_search_api_index() {
  $items = array();
  $items['internships'] = entity_import('search_api_index', '{
    "name" : "Internships",
    "machine_name" : "internships",
    "description" : null,
    "server" : "search_node",
    "item_type" : "node",
    "options" : {
      "datasource" : { "bundles" : [ "internship" ] },
      "index_directly" : 0,
      "cron_limit" : "50",
      "search_node_indexes" : "65f9284ed834ed7865ed5331f9e4aa90",
      "fields" : {
        "author" : { "type" : "integer", "entity_type" : "user" },
        "author:field_garantipartner" : { "type" : "boolean" },
        "author:field_lokation" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "taxonomy_term" },
        "author:field_profile_name" : { "type" : "text" },
        "author:field_tilbudsforpligtelser" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "taxonomy_term" },
        "author:url" : { "type" : "uri" },
        "changed" : { "type" : "date" },
        "created" : { "type" : "date" },
        "field_business_type" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "taxonomy_term" },
        "field_full_description:value" : { "type" : "text" },
        "field_image:file" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "file" },
        "field_interesseomraader" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "taxonomy_term" },
        "field_location" : { "type" : "string" },
        "field_price" : { "type" : "decimal" },
        "field_subjects_primary_school" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "taxonomy_term" },
        "field_target_group_sub" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "taxonomy_term" },
        "nid" : { "type" : "integer" },
        "search_api_language" : { "type" : "string" },
        "title" : { "type" : "text" },
        "type" : { "type" : "string" },
        "url" : { "type" : "uri" }
      },
      "data_alter_callbacks" : {
        "search_api_alter_bundle_filter" : {
          "status" : 0,
          "weight" : "-50",
          "settings" : { "default" : "1", "bundles" : [] }
        },
        "search_api_alter_add_url" : { "status" : 0, "weight" : "-49", "settings" : [] },
        "search_api_alter_add_aggregation" : { "status" : 0, "weight" : "-48", "settings" : [] },
        "search_api_alter_add_viewed_entity" : { "status" : 0, "weight" : "-47", "settings" : { "mode" : "full" } },
        "search_api_alter_add_hierarchy" : { "status" : 0, "weight" : "-46", "settings" : { "fields" : [] } },
        "search_api_alter_language_control" : {
          "status" : 0,
          "weight" : "-45",
          "settings" : { "lang_field" : "", "languages" : [] }
        },
        "search_api_alter_node_access" : { "status" : 0, "weight" : "-44", "settings" : [] },
        "location" : {
          "status" : 1,
          "weight" : "-43",
          "settings" : { "field_name" : "field_location" }
        },
        "search_api_alter_node_status" : { "status" : 1, "weight" : "-42", "settings" : [] },
        "exclude" : {
          "status" : 0,
          "weight" : "-41",
          "settings" : { "fields" : { "name" : "", "values" : "" } }
        }
      },
      "processors" : {
        "search_api_case_ignore" : {
          "status" : 0,
          "weight" : "0",
          "settings" : { "fields" : { "title" : true, "author:field_profile_name" : true } }
        },
        "search_api_html_filter" : {
          "status" : 0,
          "weight" : "10",
          "settings" : { "fields" : [], "title" : 0, "alt" : 0, "tags" : "" }
        },
        "search_api_transliteration" : {
          "status" : 0,
          "weight" : "15",
          "settings" : { "fields" : { "title" : true, "author:field_profile_name" : true } }
        },
        "search_api_tokenizer" : {
          "status" : 0,
          "weight" : "20",
          "settings" : {
            "fields" : { "title" : true, "author:field_profile_name" : true },
            "spaces" : "[^[:alnum:]]",
            "ignorable" : "[\\u0027]"
          }
        },
        "search_api_stopwords" : {
          "status" : 0,
          "weight" : "30",
          "settings" : {
            "fields" : { "title" : true, "author:field_profile_name" : true },
            "file" : "",
            "stopwords" : "but\\r\\ndid\\r\\nthe this that those\\r\\netc"
          }
        },
        "search_api_porter_stemmer" : {
          "status" : 0,
          "weight" : "35",
          "settings" : {
            "fields" : { "title" : true, "author:field_profile_name" : true },
            "exceptions" : "texan=texa"
          }
        },
        "search_api_highlighting" : {
          "status" : 0,
          "weight" : "40",
          "settings" : {
            "prefix" : "\\u003Cstrong\\u003E",
            "suffix" : "\\u003C\\/strong\\u003E",
            "excerpt" : 1,
            "excerpt_length" : "256",
            "exclude_fields" : [],
            "highlight" : "always",
            "highlight_partial" : 0
          }
        }
      }
    },
    "enabled" : "1",
    "read_only" : "0"
  }');
  return $items;
}
