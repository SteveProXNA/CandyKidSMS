M:title_screen
F:G$screen_title_screen_load$0$0({2}DF,SV:S),Z,0,0,0,0,0
S:Ltitle_screen.screen_title_screen_load$st$1$62({2}DG,STtag_struct_state_object:S),R,0,0,[]
S:Ltitle_screen.screen_title_screen_load$ho$1$62({2}DG,STtag_struct_hack_object:S),R,0,0,[]
F:G$screen_title_screen_update$0$0({2}DF,SV:S),Z,0,0,0,0,0
S:Ltitle_screen.screen_title_screen_update$screen_type$1$64({2}DG,SC:U),B,1,4
S:Ltitle_screen.screen_title_screen_update$st$1$65({2}DG,STtag_struct_state_object:S),R,0,0,[]
S:Ltitle_screen.screen_title_screen_update$ho$1$65({2}DG,STtag_struct_hack_object:S),R,0,0,[]
S:Ltitle_screen.screen_title_screen_update$input$1$65({1}SC:U),R,0,0,[l]
S:Ltitle_screen.screen_title_screen_update$delay$1$65({1}SC:U),R,0,0,[e]
T:Ftitle_screen$tag_struct_hack_object[({0}S:S$hack_object_delay_test$0$0({1}SC:U),Z,0,0)({1}S:S$hack_object_mydebugger$0$0({1}SC:U),Z,0,0)({2}S:S$hack_object_invincibie$0$0({1}SC:U),Z,0,0)({3}S:S$hack_object_full_boost$0$0({1}SC:U),Z,0,0)({4}S:S$hack_object_trees_type$0$0({1}SC:U),Z,0,0)({5}S:S$hack_object_exits_type$0$0({1}SC:U),Z,0,0)({6}S:S$hack_object_difficulty$0$0({1}SC:U),Z,0,0)({7}S:S$hack_object_pace_speed$0$0({1}SC:U),Z,0,0)({8}S:S$hack_object_world_data$0$0({1}SC:U),Z,0,0)({9}S:S$hack_object_round_data$0$0({1}SC:U),Z,0,0)({10}S:S$hack_object_music_data$0$0({1}SC:U),Z,0,0)({11}S:S$hack_object_sound_data$0$0({1}SC:U),Z,0,0)({12}S:S$hack_object_enemy_move$0$0({3}DA3d,SC:U),Z,0,0)]
T:Ftitle_screen$tag_struct_frame_object[({0}S:S$frame_count$0$0({2}SI:U),Z,0,0)]
T:Ftitle_screen$tag_struct_delay_object[({0}S:S$delay_value$0$0({2}SI:U),Z,0,0)({2}S:S$delay_timer$0$0({2}SI:U),Z,0,0)]
T:Ftitle_screen$tag_struct_state_object[({0}S:S$state_object_availables$0$0({1}SC:U),Z,0,0)({1}S:S$state_object_localcheat$0$0({1}SC:U),Z,0,0)({2}S:S$state_object_high_score$0$0({2}SI:U),Z,0,0)({4}S:S$state_object_trees_type$0$0({1}SC:U),Z,0,0)({5}S:S$state_object_exits_type$0$0({1}SC:U),Z,0,0)({6}S:S$state_object_difficulty$0$0({1}SC:U),Z,0,0)({7}S:S$state_object_pace_speed$0$0({1}SC:U),Z,0,0)({8}S:S$state_object_world_data$0$0({1}SC:U),Z,0,0)({9}S:S$state_object_round_data$0$0({1}SC:U),Z,0,0)({10}S:S$state_object_actor_kill$0$0({1}SC:U),Z,0,0)({11}S:S$state_object_fight_type$0$0({1}SC:U),Z,0,0)({12}S:S$state_object_curr_screen$0$0({1}SC:U),Z,0,0)({13}S:S$state_object_next_screen$0$0({1}SC:U),Z,0,0)]
T:Ftitle_screen$tag_struct_reset_object[({0}S:S$reset_value$0$0({1}SC:U),Z,0,0)({1}S:S$reset_timer$0$0({1}SC:U),Z,0,0)]
S:G$global_hack_object$0$0({15}STtag_struct_hack_object:S),E,0,0
S:G$global_state_object$0$0({14}STtag_struct_state_object:S),E,0,0
S:G$global_delay_object$0$0({4}STtag_struct_delay_object:S),E,0,0
S:G$global_frame_object$0$0({2}STtag_struct_frame_object:S),E,0,0
S:G$global_reset_object$0$0({2}STtag_struct_reset_object:S),E,0,0
S:G$locale_object_number$0$0({0}DA0d,DG,SC:U),E,0,0
S:Ftitle_screen$event_stage$0$0({1}SC:U),E,0,0
S:Ftitle_screen$flash_count$0$0({1}SC:U),E,0,0
S:Ftitle_screen$cheat_count$0$0({1}SC:U),E,0,0
S:Ftitle_screen$distance$0$0({1}SC:U),E,0,0
S:G$engine_audio_manager_music_play$0$0({2}DF,SV:S),C,0,0
S:G$engine_audio_manager_music_play_norepeat$0$0({2}DF,SV:S),C,0,0
S:G$engine_audio_manager_music_resume$0$0({2}DF,SV:S),C,0,0
S:G$engine_audio_manager_music_stop$0$0({2}DF,SV:S),C,0,0
S:G$engine_audio_manager_sfx_play$0$0({2}DF,SV:S),C,0,0
S:G$engine_font_manager_draw_char$0$0({2}DF,SV:S),C,0,0
S:G$engine_font_manager_draw_text$0$0({2}DF,SV:S),C,0,0
S:G$engine_font_manager_draw_data$0$0({2}DF,SV:S),C,0,0
S:G$engine_hack_manager_init$0$0({2}DF,SV:S),C,0,0
S:G$engine_hack_manager_load$0$0({2}DF,SV:S),C,0,0
S:G$engine_hack_manager_invert$0$0({2}DF,SV:S),C,0,0
S:G$engine_input_manager_update$0$0({2}DF,SV:S),C,0,0
S:G$engine_input_manager_hold$0$0({2}DF,SC:U),C,0,0
S:G$engine_input_manager_move$0$0({2}DF,SC:U),C,0,0
S:G$engine_input_manager_direction$0$0({2}DF,SC:U),C,0,0
S:G$engine_locale_manager_draw_text$0$0({2}DF,SV:S),C,0,0
S:G$engine_option_manager_init$0$0({2}DF,SV:S),C,0,0
S:G$engine_option_manager_update$0$0({2}DF,SV:S),C,0,0
S:G$engine_option_manager_clear$0$0({2}DF,SV:S),C,0,0
S:G$engine_option_manager_draw_actor$0$0({2}DF,SV:S),C,0,0
S:G$engine_option_manager_text_kid$0$0({2}DF,SV:S),C,0,0
S:G$engine_option_manager_text_kid_no$0$0({2}DF,SV:S),C,0,0
S:G$engine_option_manager_text_enemy$0$0({2}DF,SV:S),C,0,0
S:G$engine_option_manager_text_enemy_no$0$0({2}DF,SV:S),C,0,0
S:G$engine_option_manager_text_start$0$0({2}DF,SV:S),C,0,0
S:G$engine_option_manager_draw_bonus$0$0({2}DF,SV:S),C,0,0
S:G$engine_option_manager_draw_candy$0$0({2}DF,SV:S),C,0,0
S:G$engine_option_manager_text_tree$0$0({2}DF,SV:S),C,0,0
S:G$engine_option_manager_text_exit$0$0({2}DF,SV:S),C,0,0
S:G$engine_option_manager_option_tree$0$0({2}DF,SV:S),C,0,0
S:G$engine_option_manager_option_exit$0$0({2}DF,SV:S),C,0,0
S:G$engine_option_manager_text_other$0$0({2}DF,SV:S),C,0,0
S:G$engine_option_manager_option_world$0$0({2}DF,SV:S),C,0,0
S:G$engine_option_manager_option_round$0$0({2}DF,SV:S),C,0,0
S:G$engine_option_manager_option_diff$0$0({2}DF,SV:S),C,0,0
S:G$engine_state_manager_init$0$0({2}DF,SV:S),C,0,0
S:G$engine_state_manager_fight$0$0({2}DF,SV:S),C,0,0
S:G$engine_delay_manager_load$0$0({2}DF,SV:S),C,0,0
S:G$engine_delay_manager_update$0$0({2}DF,SC:U),C,0,0
S:G$engine_delay_manager_draw$0$0({2}DF,SV:S),C,0,0
S:G$engine_frame_manager_load$0$0({2}DF,SV:S),C,0,0
S:G$engine_frame_manager_update$0$0({2}DF,SV:S),C,0,0
S:G$engine_frame_manager_draw$0$0({2}DF,SV:S),C,0,0
S:G$engine_reset_manager_load$0$0({2}DF,SV:S),C,0,0
S:G$engine_reset_manager_update$0$0({2}DF,SC:U),C,0,0
S:G$engine_reset_manager_reset$0$0({2}DF,SV:S),C,0,0
S:G$devkit_SMS_init$0$0({2}DF,SV:S),C,0,0
S:G$devkit_SMS_displayOn$0$0({2}DF,SV:S),C,0,0
S:G$devkit_SMS_displayOff$0$0({2}DF,SV:S),C,0,0
S:G$devkit_SMS_mapROMBank$0$0({2}DF,SV:S),C,0,0
S:G$devkit_SMS_enableSRAM$0$0({2}DF,SV:S),C,0,0
S:G$devkit_SMS_enableSRAMBank$0$0({2}DF,SV:S),C,0,0
S:G$devkit_SMS_disableSRAM$0$0({2}DF,SV:S),C,0,0
S:G$devkit_SMS_SRAM$0$0({2}DF,DG,SC:U),C,0,0
S:G$devkit_SMS_setSpriteMode$0$0({2}DF,SV:S),C,0,0
S:G$devkit_SMS_useFirstHalfTilesforSprites_False$0$0({2}DF,SV:S),C,0,0
S:G$devkit_SMS_useFirstHalfTilesforSprites_True$0$0({2}DF,SV:S),C,0,0
S:G$devkit_SMS_VDPturnOnFeature$0$0({2}DF,SV:S),C,0,0
S:G$devkit_SMS_loadPSGaidencompressedTiles$0$0({2}DF,SV:S),C,0,0
S:G$devkit_SMS_loadSTMcompressedTileMap$0$0({2}DF,SV:S),C,0,0
S:G$devkit_SMS_loadBGPalette$0$0({2}DF,SV:S),C,0,0
S:G$devkit_SMS_loadSpritePalette$0$0({2}DF,SV:S),C,0,0
S:G$devkit_SMS_setSpritePaletteColor$0$0({2}DF,SV:S),C,0,0
S:G$devkit_SMS_setNextTileatXY$0$0({2}DF,SV:S),C,0,0
S:G$devkit_SMS_setTile$0$0({2}DF,SV:S),C,0,0
S:G$devkit_SMS_setTilePriority$0$0({2}DF,SV:S),C,0,0
S:G$devkit_SMS_addSprite$0$0({2}DF,SV:S),C,0,0
S:G$devkit_SMS_initSprites$0$0({2}DF,SV:S),C,0,0
S:G$devkit_SMS_finalizeSprites$0$0({2}DF,SV:S),C,0,0
S:G$devkit_SMS_waitForVBlank$0$0({2}DF,SV:S),C,0,0
S:G$devkit_SMS_copySpritestoSAT$0$0({2}DF,SV:S),C,0,0
S:G$devkit_UNSAFE_SMS_copySpritestoSAT$0$0({2}DF,SV:S),C,0,0
S:G$devkit_SMS_queryPauseRequested$0$0({2}DF,SC:U),C,0,0
S:G$devkit_SMS_resetPauseRequest$0$0({2}DF,SV:S),C,0,0
S:G$devkit_isCollisionDetected$0$0({2}DF,SC:U),C,0,0
S:G$devkit_SMS_getKeysStatus$0$0({2}DF,SI:U),C,0,0
S:G$devkit_SPRITEMODE_NORMAL$0$0({2}DF,SC:U),C,0,0
S:G$devkit_VDPFEATURE_HIDEFIRSTCOL$0$0({2}DF,SI:U),C,0,0
S:G$devkit_TILE_PRIORITY$0$0({2}DF,SI:U),C,0,0
S:G$devkit_TILE_USE_SPRITE_PALETTE$0$0({2}DF,SI:U),C,0,0
S:G$atof$0$0({2}DF,SF:S),C,0,0
S:G$atoi$0$0({2}DF,SI:S),C,0,0
S:G$atol$0$0({2}DF,SL:S),C,0,0
S:G$_uitoa$0$0({2}DF,SV:S),C,0,0
S:G$_itoa$0$0({2}DF,SV:S),C,0,0
S:G$_ultoa$0$0({2}DF,SV:S),C,0,0
S:G$_ltoa$0$0({2}DF,SV:S),C,0,0
S:G$rand$0$0({2}DF,SI:S),C,0,0
S:G$srand$0$0({2}DF,SV:S),C,0,0
S:G$calloc$0$0({2}DF,DG,SV:S),C,0,0
S:G$malloc$0$0({2}DF,DG,SV:S),C,0,0
S:G$realloc$0$0({2}DF,DG,SV:S),C,0,0
S:G$free$0$0({2}DF,SV:S),C,0,0
S:G$abs$0$0({2}DF,SI:S),C,0,0
S:G$labs$0$0({2}DF,SL:S),C,0,0
S:G$mblen$0$0({2}DF,SI:S),C,0,0
S:G$mbtowc$0$0({2}DF,SI:S),C,0,0
S:G$wctomb$0$0({2}DF,SI:S),C,0,0
S:G$mbstowcs$0$0({2}DF,SI:U),C,0,0
S:G$wcstombs$0$0({2}DF,SI:U),C,0,0
