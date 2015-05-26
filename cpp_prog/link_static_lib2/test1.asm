
libtest1.so:     file format elf64-x86-64

Disassembly of section .init:

0000000000002418 <_init>:
    2418:	48 83 ec 08          	sub    $0x8,%rsp
    241c:	e8 3f 05 00 00       	callq  2960 <call_gmon_start>
    2421:	e8 da 05 00 00       	callq  2a00 <frame_dummy>
    2426:	e8 05 1a 00 00       	callq  3e30 <__do_global_ctors_aux>
    242b:	48 83 c4 08          	add    $0x8,%rsp
    242f:	c3                   	retq   
Disassembly of section .plt:

0000000000002430 <_ZNSt12_Vector_baseISsSaISsEED2Ev@plt-0x10>:
    2430:	ff 35 fa 2d 20 00    	pushq  2108922(%rip)        # 205230 <_GLOBAL_OFFSET_TABLE_+0x8>
    2436:	ff 25 fc 2d 20 00    	jmpq   *2108924(%rip)        # 205238 <_GLOBAL_OFFSET_TABLE_+0x10>
    243c:	0f 1f 40 00          	nopl   0x0(%rax)

0000000000002440 <_ZNSt12_Vector_baseISsSaISsEED2Ev@plt>:
    2440:	ff 25 fa 2d 20 00    	jmpq   *2108922(%rip)        # 205240 <_GLOBAL_OFFSET_TABLE_+0x18>
    2446:	68 00 00 00 00       	pushq  $0x0
    244b:	e9 e0 ff ff ff       	jmpq   2430 <_init+0x18>

0000000000002450 <_ZNSt12_Vector_baseISsSaISsEE12_Vector_implD1Ev@plt>:
    2450:	ff 25 f2 2d 20 00    	jmpq   *2108914(%rip)        # 205248 <_GLOBAL_OFFSET_TABLE_+0x20>
    2456:	68 01 00 00 00       	pushq  $0x1
    245b:	e9 d0 ff ff ff       	jmpq   2430 <_init+0x18>

0000000000002460 <_ZSt20__throw_length_errorPKc@plt>:
    2460:	ff 25 ea 2d 20 00    	jmpq   *2108906(%rip)        # 205250 <_GLOBAL_OFFSET_TABLE_+0x28>
    2466:	68 02 00 00 00       	pushq  $0x2
    246b:	e9 c0 ff ff ff       	jmpq   2430 <_init+0x18>

0000000000002470 <_ZNKSt6vectorISsSaISsEE8max_sizeEv@plt>:
    2470:	ff 25 e2 2d 20 00    	jmpq   *2108898(%rip)        # 205258 <_GLOBAL_OFFSET_TABLE_+0x30>
    2476:	68 03 00 00 00       	pushq  $0x3
    247b:	e9 b0 ff ff ff       	jmpq   2430 <_init+0x18>

0000000000002480 <_ZSt8_DestroyIN9__gnu_cxx17__normal_iteratorIPSsSt6vectorISsSaISsEEEEEvT_S7_@plt>:
    2480:	ff 25 da 2d 20 00    	jmpq   *2108890(%rip)        # 205260 <_GLOBAL_OFFSET_TABLE_+0x38>
    2486:	68 04 00 00 00       	pushq  $0x4
    248b:	e9 a0 ff ff ff       	jmpq   2430 <_init+0x18>

0000000000002490 <_ZSt10_ConstructISsSsEvPT_RKT0_@plt>:
    2490:	ff 25 d2 2d 20 00    	jmpq   *2108882(%rip)        # 205268 <_GLOBAL_OFFSET_TABLE_+0x40>
    2496:	68 05 00 00 00       	pushq  $0x5
    249b:	e9 90 ff ff ff       	jmpq   2430 <_init+0x18>

00000000000024a0 <_ZNSaISsED1Ev@plt>:
    24a0:	ff 25 ca 2d 20 00    	jmpq   *2108874(%rip)        # 205270 <_GLOBAL_OFFSET_TABLE_+0x48>
    24a6:	68 06 00 00 00       	pushq  $0x6
    24ab:	e9 80 ff ff ff       	jmpq   2430 <_init+0x18>

00000000000024b0 <_ZN9__gnu_cxx17__normal_iteratorIPKSsSt6vectorISsSaISsEEEC1ERKS2_@plt>:
    24b0:	ff 25 c2 2d 20 00    	jmpq   *2108866(%rip)        # 205278 <_GLOBAL_OFFSET_TABLE_+0x50>
    24b6:	68 07 00 00 00       	pushq  $0x7
    24bb:	e9 70 ff ff ff       	jmpq   2430 <_init+0x18>

00000000000024c0 <_ZNSt12_Vector_baseISsSaISsEEC2ERKS0_@plt>:
    24c0:	ff 25 ba 2d 20 00    	jmpq   *2108858(%rip)        # 205280 <_GLOBAL_OFFSET_TABLE_+0x58>
    24c6:	68 08 00 00 00       	pushq  $0x8
    24cb:	e9 60 ff ff ff       	jmpq   2430 <_init+0x18>

00000000000024d0 <_ZNSt6vectorISsSaISsEE5beginEv@plt>:
    24d0:	ff 25 b2 2d 20 00    	jmpq   *2108850(%rip)        # 205288 <_GLOBAL_OFFSET_TABLE_+0x60>
    24d6:	68 09 00 00 00       	pushq  $0x9
    24db:	e9 50 ff ff ff       	jmpq   2430 <_init+0x18>

00000000000024e0 <_ZdlPv@plt>:
    24e0:	ff 25 aa 2d 20 00    	jmpq   *2108842(%rip)        # 205290 <_GLOBAL_OFFSET_TABLE_+0x68>
    24e6:	68 0a 00 00 00       	pushq  $0xa
    24eb:	e9 40 ff ff ff       	jmpq   2430 <_init+0x18>

00000000000024f0 <_ZNKSt6vectorISsSaISsEE5beginEv@plt>:
    24f0:	ff 25 a2 2d 20 00    	jmpq   *2108834(%rip)        # 205298 <_GLOBAL_OFFSET_TABLE_+0x70>
    24f6:	68 0b 00 00 00       	pushq  $0xb
    24fb:	e9 30 ff ff ff       	jmpq   2430 <_init+0x18>

0000000000002500 <__cxa_rethrow@plt>:
    2500:	ff 25 9a 2d 20 00    	jmpq   *2108826(%rip)        # 2052a0 <_GLOBAL_OFFSET_TABLE_+0x78>
    2506:	68 0c 00 00 00       	pushq  $0xc
    250b:	e9 20 ff ff ff       	jmpq   2430 <_init+0x18>

0000000000002510 <_ZNSt8ios_base4InitC1Ev@plt>:
    2510:	ff 25 92 2d 20 00    	jmpq   *2108818(%rip)        # 2052a8 <_GLOBAL_OFFSET_TABLE_+0x80>
    2516:	68 0d 00 00 00       	pushq  $0xd
    251b:	e9 10 ff ff ff       	jmpq   2430 <_init+0x18>

0000000000002520 <_ZNSt12_Vector_baseISsSaISsEE19_M_get_Tp_allocatorEv@plt>:
    2520:	ff 25 8a 2d 20 00    	jmpq   *2108810(%rip)        # 2052b0 <_GLOBAL_OFFSET_TABLE_+0x88>
    2526:	68 0e 00 00 00       	pushq  $0xe
    252b:	e9 00 ff ff ff       	jmpq   2430 <_init+0x18>

0000000000002530 <_ZNSt15__copy_backwardILb0ESt26random_access_iterator_tagE6copy_bIPSsS3_EET0_T_S5_S4_@plt>:
    2530:	ff 25 82 2d 20 00    	jmpq   *2108802(%rip)        # 2052b8 <_GLOBAL_OFFSET_TABLE_+0x90>
    2536:	68 0f 00 00 00       	pushq  $0xf
    253b:	e9 f0 fe ff ff       	jmpq   2430 <_init+0x18>

0000000000002540 <_ZSt8_DestroyISsEvPT_@plt>:
    2540:	ff 25 7a 2d 20 00    	jmpq   *2108794(%rip)        # 2052c0 <_GLOBAL_OFFSET_TABLE_+0x98>
    2546:	68 10 00 00 00       	pushq  $0x10
    254b:	e9 e0 fe ff ff       	jmpq   2430 <_init+0x18>

0000000000002550 <_ZNSaISsEC1ERKS_@plt>:
    2550:	ff 25 72 2d 20 00    	jmpq   *2108786(%rip)        # 2052c8 <_GLOBAL_OFFSET_TABLE_+0xa0>
    2556:	68 11 00 00 00       	pushq  $0x11
    255b:	e9 d0 fe ff ff       	jmpq   2430 <_init+0x18>

0000000000002560 <_ZNK9__gnu_cxx17__normal_iteratorIPSsSt6vectorISsSaISsEEE4baseEv@plt>:
    2560:	ff 25 6a 2d 20 00    	jmpq   *2108778(%rip)        # 2052d0 <_GLOBAL_OFFSET_TABLE_+0xa8>
    2566:	68 12 00 00 00       	pushq  $0x12
    256b:	e9 c0 fe ff ff       	jmpq   2430 <_init+0x18>

0000000000002570 <_ZNSsC1ERKSs@plt>:
    2570:	ff 25 62 2d 20 00    	jmpq   *2108770(%rip)        # 2052d8 <_GLOBAL_OFFSET_TABLE_+0xb0>
    2576:	68 13 00 00 00       	pushq  $0x13
    257b:	e9 b0 fe ff ff       	jmpq   2430 <_init+0x18>

0000000000002580 <__cxa_atexit@plt>:
    2580:	ff 25 5a 2d 20 00    	jmpq   *2108762(%rip)        # 2052e0 <_GLOBAL_OFFSET_TABLE_+0xb8>
    2586:	68 14 00 00 00       	pushq  $0x14
    258b:	e9 a0 fe ff ff       	jmpq   2430 <_init+0x18>

0000000000002590 <_ZnwmPv@plt>:
    2590:	ff 25 52 2d 20 00    	jmpq   *2108754(%rip)        # 2052e8 <_GLOBAL_OFFSET_TABLE_+0xc0>
    2596:	68 15 00 00 00       	pushq  $0x15
    259b:	e9 90 fe ff ff       	jmpq   2430 <_init+0x18>

00000000000025a0 <_ZNSt12_Vector_baseISsSaISsEE13_M_deallocateEPSsm@plt>:
    25a0:	ff 25 4a 2d 20 00    	jmpq   *2108746(%rip)        # 2052f0 <_GLOBAL_OFFSET_TABLE_+0xc8>
    25a6:	68 16 00 00 00       	pushq  $0x16
    25ab:	e9 80 fe ff ff       	jmpq   2430 <_init+0x18>

00000000000025b0 <_ZSt13__destroy_auxIPSsEvT_S1_12__false_type@plt>:
    25b0:	ff 25 42 2d 20 00    	jmpq   *2108738(%rip)        # 2052f8 <_GLOBAL_OFFSET_TABLE_+0xd0>
    25b6:	68 17 00 00 00       	pushq  $0x17
    25bb:	e9 70 fe ff ff       	jmpq   2430 <_init+0x18>

00000000000025c0 <_Z5hellov@plt>:
    25c0:	ff 25 3a 2d 20 00    	jmpq   *2108730(%rip)        # 205300 <_GLOBAL_OFFSET_TABLE_+0xd8>
    25c6:	68 18 00 00 00       	pushq  $0x18
    25cb:	e9 60 fe ff ff       	jmpq   2430 <_init+0x18>

00000000000025d0 <_ZNSt6vectorISsSaISsEE13_M_insert_auxEN9__gnu_cxx17__normal_iteratorIPSsS1_EERKSs@plt>:
    25d0:	ff 25 32 2d 20 00    	jmpq   *2108722(%rip)        # 205308 <_GLOBAL_OFFSET_TABLE_+0xe0>
    25d6:	68 19 00 00 00       	pushq  $0x19
    25db:	e9 50 fe ff ff       	jmpq   2430 <_init+0x18>

00000000000025e0 <_ZNSt8ios_base4InitD1Ev@plt>:
    25e0:	ff 25 2a 2d 20 00    	jmpq   *2108714(%rip)        # 205310 <_GLOBAL_OFFSET_TABLE_+0xe8>
    25e6:	68 1a 00 00 00       	pushq  $0x1a
    25eb:	e9 40 fe ff ff       	jmpq   2430 <_init+0x18>

00000000000025f0 <_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@plt>:
    25f0:	ff 25 22 2d 20 00    	jmpq   *2108706(%rip)        # 205318 <_GLOBAL_OFFSET_TABLE_+0xf0>
    25f6:	68 1b 00 00 00       	pushq  $0x1b
    25fb:	e9 30 fe ff ff       	jmpq   2430 <_init+0x18>

0000000000002600 <_ZNSt12_Vector_baseISsSaISsEE11_M_allocateEm@plt>:
    2600:	ff 25 1a 2d 20 00    	jmpq   *2108698(%rip)        # 205320 <_GLOBAL_OFFSET_TABLE_+0xf8>
    2606:	68 1c 00 00 00       	pushq  $0x1c
    260b:	e9 20 fe ff ff       	jmpq   2430 <_init+0x18>

0000000000002610 <_ZNSsD1Ev@plt>:
    2610:	ff 25 12 2d 20 00    	jmpq   *2108690(%rip)        # 205328 <_GLOBAL_OFFSET_TABLE_+0x100>
    2616:	68 1d 00 00 00       	pushq  $0x1d
    261b:	e9 10 fe ff ff       	jmpq   2430 <_init+0x18>

0000000000002620 <_ZN9__gnu_cxx13new_allocatorISsE9constructEPSsRKSs@plt>:
    2620:	ff 25 0a 2d 20 00    	jmpq   *2108682(%rip)        # 205330 <_GLOBAL_OFFSET_TABLE_+0x108>
    2626:	68 1e 00 00 00       	pushq  $0x1e
    262b:	e9 00 fe ff ff       	jmpq   2430 <_init+0x18>

0000000000002630 <_ZN9__gnu_cxx13new_allocatorISsED2Ev@plt>:
    2630:	ff 25 02 2d 20 00    	jmpq   *2108674(%rip)        # 205338 <_GLOBAL_OFFSET_TABLE_+0x110>
    2636:	68 1f 00 00 00       	pushq  $0x1f
    263b:	e9 f0 fd ff ff       	jmpq   2430 <_init+0x18>

0000000000002640 <_ZN9__gnu_cxxneIPSsSt6vectorISsSaISsEEEEbRKNS_17__normal_iteratorIT_T0_EESA_@plt>:
    2640:	ff 25 fa 2c 20 00    	jmpq   *2108666(%rip)        # 205340 <_GLOBAL_OFFSET_TABLE_+0x118>
    2646:	68 20 00 00 00       	pushq  $0x20
    264b:	e9 e0 fd ff ff       	jmpq   2430 <_init+0x18>

0000000000002650 <_ZNSolsEPKv@plt>:
    2650:	ff 25 f2 2c 20 00    	jmpq   *2108658(%rip)        # 205348 <_GLOBAL_OFFSET_TABLE_+0x120>
    2656:	68 21 00 00 00       	pushq  $0x21
    265b:	e9 d0 fd ff ff       	jmpq   2430 <_init+0x18>

0000000000002660 <_ZNKSt6vectorISsSaISsEE3endEv@plt>:
    2660:	ff 25 ea 2c 20 00    	jmpq   *2108650(%rip)        # 205350 <_GLOBAL_OFFSET_TABLE_+0x128>
    2666:	68 22 00 00 00       	pushq  $0x22
    266b:	e9 c0 fd ff ff       	jmpq   2430 <_init+0x18>

0000000000002670 <_ZSt8_DestroyIPSsSsEvT_S1_SaIT0_E@plt>:
    2670:	ff 25 e2 2c 20 00    	jmpq   *2108642(%rip)        # 205358 <_GLOBAL_OFFSET_TABLE_+0x130>
    2676:	68 23 00 00 00       	pushq  $0x23
    267b:	e9 b0 fd ff ff       	jmpq   2430 <_init+0x18>

0000000000002680 <__cxa_finalize@plt>:
    2680:	ff 25 da 2c 20 00    	jmpq   *2108634(%rip)        # 205360 <_GLOBAL_OFFSET_TABLE_+0x138>
    2686:	68 24 00 00 00       	pushq  $0x24
    268b:	e9 a0 fd ff ff       	jmpq   2430 <_init+0x18>

0000000000002690 <_ZN9__gnu_cxx13new_allocatorISsE8allocateEmPKv@plt>:
    2690:	ff 25 d2 2c 20 00    	jmpq   *2108626(%rip)        # 205368 <_GLOBAL_OFFSET_TABLE_+0x140>
    2696:	68 25 00 00 00       	pushq  $0x25
    269b:	e9 90 fd ff ff       	jmpq   2430 <_init+0x18>

00000000000026a0 <_ZNSolsEm@plt>:
    26a0:	ff 25 ca 2c 20 00    	jmpq   *2108618(%rip)        # 205370 <_GLOBAL_OFFSET_TABLE_+0x148>
    26a6:	68 26 00 00 00       	pushq  $0x26
    26ab:	e9 80 fd ff ff       	jmpq   2430 <_init+0x18>

00000000000026b0 <_ZNSaISsED2Ev@plt>:
    26b0:	ff 25 c2 2c 20 00    	jmpq   *2108610(%rip)        # 205378 <_GLOBAL_OFFSET_TABLE_+0x150>
    26b6:	68 27 00 00 00       	pushq  $0x27
    26bb:	e9 70 fd ff ff       	jmpq   2430 <_init+0x18>

00000000000026c0 <_ZNSsC1EPKcRKSaIcE@plt>:
    26c0:	ff 25 ba 2c 20 00    	jmpq   *2108602(%rip)        # 205380 <_GLOBAL_OFFSET_TABLE_+0x158>
    26c6:	68 28 00 00 00       	pushq  $0x28
    26cb:	e9 60 fd ff ff       	jmpq   2430 <_init+0x18>

00000000000026d0 <_ZSt8_DestroyIN9__gnu_cxx17__normal_iteratorIPSsSt6vectorISsSaISsEEEESsEvT_S7_SaIT0_E@plt>:
    26d0:	ff 25 b2 2c 20 00    	jmpq   *2108594(%rip)        # 205388 <_GLOBAL_OFFSET_TABLE_+0x160>
    26d6:	68 29 00 00 00       	pushq  $0x29
    26db:	e9 50 fd ff ff       	jmpq   2430 <_init+0x18>

00000000000026e0 <_ZN9__gnu_cxx13new_allocatorISsE10deallocateEPSsm@plt>:
    26e0:	ff 25 aa 2c 20 00    	jmpq   *2108586(%rip)        # 205390 <_GLOBAL_OFFSET_TABLE_+0x168>
    26e6:	68 2a 00 00 00       	pushq  $0x2a
    26eb:	e9 40 fd ff ff       	jmpq   2430 <_init+0x18>

00000000000026f0 <_ZNSt6vectorISsSaISsEE3endEv@plt>:
    26f0:	ff 25 a2 2c 20 00    	jmpq   *2108578(%rip)        # 205398 <_GLOBAL_OFFSET_TABLE_+0x170>
    26f6:	68 2b 00 00 00       	pushq  $0x2b
    26fb:	e9 30 fd ff ff       	jmpq   2430 <_init+0x18>

0000000000002700 <_ZNKSt6vectorISsSaISsEE4sizeEv@plt>:
    2700:	ff 25 9a 2c 20 00    	jmpq   *2108570(%rip)        # 2053a0 <_GLOBAL_OFFSET_TABLE_+0x178>
    2706:	68 2c 00 00 00       	pushq  $0x2c
    270b:	e9 20 fd ff ff       	jmpq   2430 <_init+0x18>

0000000000002710 <_ZNK9__gnu_cxx17__normal_iteratorIPKSsSt6vectorISsSaISsEEE4baseEv@plt>:
    2710:	ff 25 92 2c 20 00    	jmpq   *2108562(%rip)        # 2053a8 <_GLOBAL_OFFSET_TABLE_+0x180>
    2716:	68 2d 00 00 00       	pushq  $0x2d
    271b:	e9 10 fd ff ff       	jmpq   2430 <_init+0x18>

0000000000002720 <_ZNK4Test8getCountEv@plt>:
    2720:	ff 25 8a 2c 20 00    	jmpq   *2108554(%rip)        # 2053b0 <_GLOBAL_OFFSET_TABLE_+0x188>
    2726:	68 2e 00 00 00       	pushq  $0x2e
    272b:	e9 00 fd ff ff       	jmpq   2430 <_init+0x18>

0000000000002730 <_ZNK9__gnu_cxx17__normal_iteratorIPSsSt6vectorISsSaISsEEEdeEv@plt>:
    2730:	ff 25 82 2c 20 00    	jmpq   *2108546(%rip)        # 2053b8 <_GLOBAL_OFFSET_TABLE_+0x190>
    2736:	68 2f 00 00 00       	pushq  $0x2f
    273b:	e9 f0 fc ff ff       	jmpq   2430 <_init+0x18>

0000000000002740 <_ZN4Test6addSthERKSs@plt>:
    2740:	ff 25 7a 2c 20 00    	jmpq   *2108538(%rip)        # 2053c0 <_GLOBAL_OFFSET_TABLE_+0x198>
    2746:	68 30 00 00 00       	pushq  $0x30
    274b:	e9 e0 fc ff ff       	jmpq   2430 <_init+0x18>

0000000000002750 <_ZNSt6vectorISsSaISsEE9push_backERKSs@plt>:
    2750:	ff 25 72 2c 20 00    	jmpq   *2108530(%rip)        # 2053c8 <_GLOBAL_OFFSET_TABLE_+0x1a0>
    2756:	68 31 00 00 00       	pushq  $0x31
    275b:	e9 d0 fc ff ff       	jmpq   2430 <_init+0x18>

0000000000002760 <_ZN9__gnu_cxx17__normal_iteratorIPSsSt6vectorISsSaISsEEEppEv@plt>:
    2760:	ff 25 6a 2c 20 00    	jmpq   *2108522(%rip)        # 2053d0 <_GLOBAL_OFFSET_TABLE_+0x1a8>
    2766:	68 32 00 00 00       	pushq  $0x32
    276b:	e9 c0 fc ff ff       	jmpq   2430 <_init+0x18>

0000000000002770 <_ZSt22__uninitialized_copy_aIN9__gnu_cxx17__normal_iteratorIPSsSt6vectorISsSaISsEEEES6_SsET0_T_S8_S7_SaIT1_E@plt>:
    2770:	ff 25 62 2c 20 00    	jmpq   *2108514(%rip)        # 2053d8 <_GLOBAL_OFFSET_TABLE_+0x1b0>
    2776:	68 33 00 00 00       	pushq  $0x33
    277b:	e9 b0 fc ff ff       	jmpq   2430 <_init+0x18>

0000000000002780 <_ZN9__gnu_cxx17__normal_iteratorIPSsSt6vectorISsSaISsEEEC1ERKS1_@plt>:
    2780:	ff 25 5a 2c 20 00    	jmpq   *2108506(%rip)        # 2053e0 <_GLOBAL_OFFSET_TABLE_+0x1b8>
    2786:	68 34 00 00 00       	pushq  $0x34
    278b:	e9 a0 fc ff ff       	jmpq   2430 <_init+0x18>

0000000000002790 <_ZN4TestD1Ev@plt>:
    2790:	ff 25 52 2c 20 00    	jmpq   *2108498(%rip)        # 2053e8 <_GLOBAL_OFFSET_TABLE_+0x1c0>
    2796:	68 35 00 00 00       	pushq  $0x35
    279b:	e9 90 fc ff ff       	jmpq   2430 <_init+0x18>

00000000000027a0 <_ZStlsIcSt11char_traitsIcESaIcEERSt13basic_ostreamIT_T0_ES7_RKSbIS4_S5_T1_E@plt>:
    27a0:	ff 25 4a 2c 20 00    	jmpq   *2108490(%rip)        # 2053f0 <_GLOBAL_OFFSET_TABLE_+0x1c8>
    27a6:	68 36 00 00 00       	pushq  $0x36
    27ab:	e9 80 fc ff ff       	jmpq   2430 <_init+0x18>

00000000000027b0 <_ZNK9__gnu_cxx13new_allocatorISsE8max_sizeEv@plt>:
    27b0:	ff 25 42 2c 20 00    	jmpq   *2108482(%rip)        # 2053f8 <_GLOBAL_OFFSET_TABLE_+0x1d0>
    27b6:	68 37 00 00 00       	pushq  $0x37
    27bb:	e9 70 fc ff ff       	jmpq   2430 <_init+0x18>

00000000000027c0 <_ZSt13copy_backwardIN9__gnu_cxx17__normal_iteratorIPSsSt6vectorISsSaISsEEEES6_ET0_T_S8_S7_@plt>:
    27c0:	ff 25 3a 2c 20 00    	jmpq   *2108474(%rip)        # 205400 <_GLOBAL_OFFSET_TABLE_+0x1d8>
    27c6:	68 38 00 00 00       	pushq  $0x38
    27cb:	e9 60 fc ff ff       	jmpq   2430 <_init+0x18>

00000000000027d0 <_ZNSaIcED1Ev@plt>:
    27d0:	ff 25 32 2c 20 00    	jmpq   *2108466(%rip)        # 205408 <_GLOBAL_OFFSET_TABLE_+0x1e0>
    27d6:	68 39 00 00 00       	pushq  $0x39
    27db:	e9 50 fc ff ff       	jmpq   2430 <_init+0x18>

00000000000027e0 <_ZSt19__copy_backward_auxIPSsS0_ET0_T_S2_S1_@plt>:
    27e0:	ff 25 2a 2c 20 00    	jmpq   *2108458(%rip)        # 205410 <_GLOBAL_OFFSET_TABLE_+0x1e8>
    27e6:	68 3a 00 00 00       	pushq  $0x3a
    27eb:	e9 40 fc ff ff       	jmpq   2430 <_init+0x18>

00000000000027f0 <_ZSt18uninitialized_copyIN9__gnu_cxx17__normal_iteratorIPSsSt6vectorISsSaISsEEEES6_ET0_T_S8_S7_@plt>:
    27f0:	ff 25 22 2c 20 00    	jmpq   *2108450(%rip)        # 205418 <_GLOBAL_OFFSET_TABLE_+0x1f0>
    27f6:	68 3b 00 00 00       	pushq  $0x3b
    27fb:	e9 30 fc ff ff       	jmpq   2430 <_init+0x18>

0000000000002800 <_ZSt24__uninitialized_copy_auxIN9__gnu_cxx17__normal_iteratorIPSsSt6vectorISsSaISsEEEES6_ET0_T_S8_S7_12__false_type@plt>:
    2800:	ff 25 1a 2c 20 00    	jmpq   *2108442(%rip)        # 205420 <_GLOBAL_OFFSET_TABLE_+0x1f8>
    2806:	68 3c 00 00 00       	pushq  $0x3c
    280b:	e9 20 fc ff ff       	jmpq   2430 <_init+0x18>

0000000000002810 <_ZNSolsEPFRSoS_E@plt>:
    2810:	ff 25 12 2c 20 00    	jmpq   *2108434(%rip)        # 205428 <_GLOBAL_OFFSET_TABLE_+0x200>
    2816:	68 3d 00 00 00       	pushq  $0x3d
    281b:	e9 10 fc ff ff       	jmpq   2430 <_init+0x18>

0000000000002820 <_ZNSt6vectorISsSaISsEEC1ERKS0_@plt>:
    2820:	ff 25 0a 2c 20 00    	jmpq   *2108426(%rip)        # 205430 <_GLOBAL_OFFSET_TABLE_+0x208>
    2826:	68 3e 00 00 00       	pushq  $0x3e
    282b:	e9 00 fc ff ff       	jmpq   2430 <_init+0x18>

0000000000002830 <__cxa_end_catch@plt>:
    2830:	ff 25 02 2c 20 00    	jmpq   *2108418(%rip)        # 205438 <_GLOBAL_OFFSET_TABLE_+0x210>
    2836:	68 3f 00 00 00       	pushq  $0x3f
    283b:	e9 f0 fb ff ff       	jmpq   2430 <_init+0x18>

0000000000002840 <_ZSt17__throw_bad_allocv@plt>:
    2840:	ff 25 fa 2b 20 00    	jmpq   *2108410(%rip)        # 205440 <_GLOBAL_OFFSET_TABLE_+0x218>
    2846:	68 40 00 00 00       	pushq  $0x40
    284b:	e9 e0 fb ff ff       	jmpq   2430 <_init+0x18>

0000000000002850 <_ZNSt12_Vector_baseISsSaISsEE12_Vector_implC1ERKS0_@plt>:
    2850:	ff 25 f2 2b 20 00    	jmpq   *2108402(%rip)        # 205448 <_GLOBAL_OFFSET_TABLE_+0x220>
    2856:	68 41 00 00 00       	pushq  $0x41
    285b:	e9 d0 fb ff ff       	jmpq   2430 <_init+0x18>

0000000000002860 <_ZSt13__destroy_auxIN9__gnu_cxx17__normal_iteratorIPSsSt6vectorISsSaISsEEEEEvT_S7_12__false_type@plt>:
    2860:	ff 25 ea 2b 20 00    	jmpq   *2108394(%rip)        # 205450 <_GLOBAL_OFFSET_TABLE_+0x228>
    2866:	68 42 00 00 00       	pushq  $0x42
    286b:	e9 c0 fb ff ff       	jmpq   2430 <_init+0x18>

0000000000002870 <__cxa_begin_catch@plt>:
    2870:	ff 25 e2 2b 20 00    	jmpq   *2108386(%rip)        # 205458 <_GLOBAL_OFFSET_TABLE_+0x230>
    2876:	68 43 00 00 00       	pushq  $0x43
    287b:	e9 b0 fb ff ff       	jmpq   2430 <_init+0x18>

0000000000002880 <_ZNSt6vectorISsSaISsEED1Ev@plt>:
    2880:	ff 25 da 2b 20 00    	jmpq   *2108378(%rip)        # 205460 <_GLOBAL_OFFSET_TABLE_+0x238>
    2886:	68 44 00 00 00       	pushq  $0x44
    288b:	e9 a0 fb ff ff       	jmpq   2430 <_init+0x18>

0000000000002890 <_ZNSaIcEC1Ev@plt>:
    2890:	ff 25 d2 2b 20 00    	jmpq   *2108370(%rip)        # 205468 <_GLOBAL_OFFSET_TABLE_+0x240>
    2896:	68 45 00 00 00       	pushq  $0x45
    289b:	e9 90 fb ff ff       	jmpq   2430 <_init+0x18>

00000000000028a0 <_ZdlPvS_@plt>:
    28a0:	ff 25 ca 2b 20 00    	jmpq   *2108362(%rip)        # 205470 <_GLOBAL_OFFSET_TABLE_+0x248>
    28a6:	68 46 00 00 00       	pushq  $0x46
    28ab:	e9 80 fb ff ff       	jmpq   2430 <_init+0x18>

00000000000028b0 <_Znwm@plt>:
    28b0:	ff 25 c2 2b 20 00    	jmpq   *2108354(%rip)        # 205478 <_GLOBAL_OFFSET_TABLE_+0x250>
    28b6:	68 47 00 00 00       	pushq  $0x47
    28bb:	e9 70 fb ff ff       	jmpq   2430 <_init+0x18>

00000000000028c0 <_Unwind_Resume@plt>:
    28c0:	ff 25 ba 2b 20 00    	jmpq   *2108346(%rip)        # 205480 <_GLOBAL_OFFSET_TABLE_+0x258>
    28c6:	68 48 00 00 00       	pushq  $0x48
    28cb:	e9 60 fb ff ff       	jmpq   2430 <_init+0x18>

00000000000028d0 <_ZN9__gnu_cxx13new_allocatorISsEC2ERKS1_@plt>:
    28d0:	ff 25 b2 2b 20 00    	jmpq   *2108338(%rip)        # 205488 <_GLOBAL_OFFSET_TABLE_+0x260>
    28d6:	68 49 00 00 00       	pushq  $0x49
    28db:	e9 50 fb ff ff       	jmpq   2430 <_init+0x18>

00000000000028e0 <_ZN9__gnu_cxxmiIPKSsS2_St6vectorISsSaISsEEEENS_17__normal_iteratorIT_T1_E15difference_typeERKS9_RKNS6_IT0_S8_EE@plt>:
    28e0:	ff 25 aa 2b 20 00    	jmpq   *2108330(%rip)        # 205490 <_GLOBAL_OFFSET_TABLE_+0x268>
    28e6:	68 4a 00 00 00       	pushq  $0x4a
    28eb:	e9 40 fb ff ff       	jmpq   2430 <_init+0x18>

00000000000028f0 <_ZNSaISsEC2ERKS_@plt>:
    28f0:	ff 25 a2 2b 20 00    	jmpq   *2108322(%rip)        # 205498 <_GLOBAL_OFFSET_TABLE_+0x270>
    28f6:	68 4b 00 00 00       	pushq  $0x4b
    28fb:	e9 30 fb ff ff       	jmpq   2430 <_init+0x18>

0000000000002900 <_ZN4TestC1ERKSs@plt>:
    2900:	ff 25 9a 2b 20 00    	jmpq   *2108314(%rip)        # 2054a0 <_GLOBAL_OFFSET_TABLE_+0x278>
    2906:	68 4c 00 00 00       	pushq  $0x4c
    290b:	e9 20 fb ff ff       	jmpq   2430 <_init+0x18>

0000000000002910 <_ZNSsaSERKSs@plt>:
    2910:	ff 25 92 2b 20 00    	jmpq   *2108306(%rip)        # 2054a8 <_GLOBAL_OFFSET_TABLE_+0x280>
    2916:	68 4d 00 00 00       	pushq  $0x4d
    291b:	e9 10 fb ff ff       	jmpq   2430 <_init+0x18>

0000000000002920 <_ZN9__gnu_cxx13new_allocatorISsEC2Ev@plt>:
    2920:	ff 25 8a 2b 20 00    	jmpq   *2108298(%rip)        # 2054b0 <_GLOBAL_OFFSET_TABLE_+0x288>
    2926:	68 4e 00 00 00       	pushq  $0x4e
    292b:	e9 00 fb ff ff       	jmpq   2430 <_init+0x18>

0000000000002930 <_ZNSaISsEC1Ev@plt>:
    2930:	ff 25 82 2b 20 00    	jmpq   *2108290(%rip)        # 2054b8 <_GLOBAL_OFFSET_TABLE_+0x290>
    2936:	68 4f 00 00 00       	pushq  $0x4f
    293b:	e9 f0 fa ff ff       	jmpq   2430 <_init+0x18>

0000000000002940 <_ZSt8_DestroyIPSsEvT_S1_@plt>:
    2940:	ff 25 7a 2b 20 00    	jmpq   *2108282(%rip)        # 2054c0 <_GLOBAL_OFFSET_TABLE_+0x298>
    2946:	68 50 00 00 00       	pushq  $0x50
    294b:	e9 e0 fa ff ff       	jmpq   2430 <_init+0x18>

0000000000002950 <_ZNSt22__copy_backward_normalILb1ELb1EE8copy_b_nIN9__gnu_cxx17__normal_iteratorIPSsSt6vectorISsSaISsEEEES8_EET0_T_SA_S9_@plt>:
    2950:	ff 25 72 2b 20 00    	jmpq   *2108274(%rip)        # 2054c8 <_GLOBAL_OFFSET_TABLE_+0x2a0>
    2956:	68 51 00 00 00       	pushq  $0x51
    295b:	e9 d0 fa ff ff       	jmpq   2430 <_init+0x18>
Disassembly of section .text:

0000000000002960 <call_gmon_start>:
    2960:	48 83 ec 08          	sub    $0x8,%rsp
    2964:	48 8b 05 85 28 20 00 	mov    2107525(%rip),%rax        # 2051f0 <_DYNAMIC+0x1b0>
    296b:	48 85 c0             	test   %rax,%rax
    296e:	74 02                	je     2972 <call_gmon_start+0x12>
    2970:	ff d0                	callq  *%rax
    2972:	48 83 c4 08          	add    $0x8,%rsp
    2976:	c3                   	retq   
    2977:	90                   	nop    
    2978:	90                   	nop    
    2979:	90                   	nop    
    297a:	90                   	nop    
    297b:	90                   	nop    
    297c:	90                   	nop    
    297d:	90                   	nop    
    297e:	90                   	nop    
    297f:	90                   	nop    

0000000000002980 <__do_global_dtors_aux>:
    2980:	55                   	push   %rbp
    2981:	80 3d 60 2b 20 00 00 	cmpb   $0x0,2108256(%rip)        # 2054e8 <completed.6145>
    2988:	48 89 e5             	mov    %rsp,%rbp
    298b:	41 54                	push   %r12
    298d:	53                   	push   %rbx
    298e:	75 62                	jne    29f2 <__do_global_dtors_aux+0x72>
    2990:	48 83 3d 68 28 20 00 	cmpq   $0x0,2107496(%rip)        # 205200 <_DYNAMIC+0x1c0>
    2997:	00 
    2998:	74 0c                	je     29a6 <__do_global_dtors_aux+0x26>
    299a:	48 8d 3d 97 26 20 00 	lea    2107031(%rip),%rdi        # 205038 <__dso_handle>
    29a1:	e8 da fc ff ff       	callq  2680 <__cxa_finalize@plt>
    29a6:	48 8d 05 7b 26 20 00 	lea    2107003(%rip),%rax        # 205028 <__DTOR_END__>
    29ad:	4c 8d 25 6c 26 20 00 	lea    2106988(%rip),%r12        # 205020 <__DTOR_LIST__>
    29b4:	4c 29 e0             	sub    %r12,%rax
    29b7:	48 c1 f8 03          	sar    $0x3,%rax
    29bb:	48 8d 58 ff          	lea    0xffffffffffffffff(%rax),%rbx
    29bf:	48 8b 05 1a 2b 20 00 	mov    2108186(%rip),%rax        # 2054e0 <dtor_idx.6147>
    29c6:	48 39 c3             	cmp    %rax,%rbx
    29c9:	76 20                	jbe    29eb <__do_global_dtors_aux+0x6b>
    29cb:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)
    29d0:	48 83 c0 01          	add    $0x1,%rax
    29d4:	48 89 05 05 2b 20 00 	mov    %rax,2108165(%rip)        # 2054e0 <dtor_idx.6147>
    29db:	41 ff 14 c4          	callq  *(%r12,%rax,8)
    29df:	48 8b 05 fa 2a 20 00 	mov    2108154(%rip),%rax        # 2054e0 <dtor_idx.6147>
    29e6:	48 39 c3             	cmp    %rax,%rbx
    29e9:	77 e5                	ja     29d0 <__do_global_dtors_aux+0x50>
    29eb:	c6 05 f6 2a 20 00 01 	movb   $0x1,2108150(%rip)        # 2054e8 <completed.6145>
    29f2:	5b                   	pop    %rbx
    29f3:	41 5c                	pop    %r12
    29f5:	c9                   	leaveq 
    29f6:	c3                   	retq   
    29f7:	66 0f 1f 84 00 00 00 	nopw   0x0(%rax,%rax,1)
    29fe:	00 00 

0000000000002a00 <frame_dummy>:
    2a00:	55                   	push   %rbp
    2a01:	48 83 3d 27 26 20 00 	cmpq   $0x0,2106919(%rip)        # 205030 <__JCR_END__>
    2a08:	00 
    2a09:	48 89 e5             	mov    %rsp,%rbp
    2a0c:	74 1a                	je     2a28 <frame_dummy+0x28>
    2a0e:	48 8b 05 e3 27 20 00 	mov    2107363(%rip),%rax        # 2051f8 <_DYNAMIC+0x1b8>
    2a15:	48 85 c0             	test   %rax,%rax
    2a18:	74 0e                	je     2a28 <frame_dummy+0x28>
    2a1a:	48 8d 3d 0f 26 20 00 	lea    2106895(%rip),%rdi        # 205030 <__JCR_END__>
    2a21:	49 89 c3             	mov    %rax,%r11
    2a24:	c9                   	leaveq 
    2a25:	41 ff e3             	jmpq   *%r11
    2a28:	c9                   	leaveq 
    2a29:	c3                   	retq   
    2a2a:	90                   	nop    
    2a2b:	90                   	nop    

0000000000002a2c <_Z41__static_initialization_and_destruction_0ii>:
    2a2c:	55                   	push   %rbp
    2a2d:	48 89 e5             	mov    %rsp,%rbp
    2a30:	48 83 ec 10          	sub    $0x10,%rsp
    2a34:	89 7d fc             	mov    %edi,0xfffffffffffffffc(%rbp)
    2a37:	89 75 f8             	mov    %esi,0xfffffffffffffff8(%rbp)
    2a3a:	83 7d fc 01          	cmpl   $0x1,0xfffffffffffffffc(%rbp)
    2a3e:	75 2d                	jne    2a6d <_Z41__static_initialization_and_destruction_0ii+0x41>
    2a40:	81 7d f8 ff ff 00 00 	cmpl   $0xffff,0xfffffffffffffff8(%rbp)
    2a47:	75 24                	jne    2a6d <_Z41__static_initialization_and_destruction_0ii+0x41>
    2a49:	48 8d 3d 9c 2a 20 00 	lea    2108060(%rip),%rdi        # 2054ec <_ZSt8__ioinit>
    2a50:	e8 bb fa ff ff       	callq  2510 <_ZNSt8ios_base4InitC1Ev@plt>
    2a55:	48 8b 15 b4 27 20 00 	mov    2107316(%rip),%rdx        # 205210 <_DYNAMIC+0x1d0>
    2a5c:	be 00 00 00 00       	mov    $0x0,%esi
    2a61:	48 8d 3d 1e 00 00 00 	lea    30(%rip),%rdi        # 2a86 <__tcf_0>
    2a68:	e8 13 fb ff ff       	callq  2580 <__cxa_atexit@plt>
    2a6d:	c9                   	leaveq 
    2a6e:	c3                   	retq   
    2a6f:	90                   	nop    

0000000000002a70 <_GLOBAL__I__Z7saySth1v>:
    2a70:	55                   	push   %rbp
    2a71:	48 89 e5             	mov    %rsp,%rbp
    2a74:	be ff ff 00 00       	mov    $0xffff,%esi
    2a79:	bf 01 00 00 00       	mov    $0x1,%edi
    2a7e:	e8 a9 ff ff ff       	callq  2a2c <_Z41__static_initialization_and_destruction_0ii>
    2a83:	c9                   	leaveq 
    2a84:	c3                   	retq   
    2a85:	90                   	nop    

0000000000002a86 <__tcf_0>:
    2a86:	55                   	push   %rbp
    2a87:	48 89 e5             	mov    %rsp,%rbp
    2a8a:	48 83 ec 10          	sub    $0x10,%rsp
    2a8e:	48 89 7d f8          	mov    %rdi,0xfffffffffffffff8(%rbp)
    2a92:	48 8d 3d 53 2a 20 00 	lea    2107987(%rip),%rdi        # 2054ec <_ZSt8__ioinit>
    2a99:	e8 42 fb ff ff       	callq  25e0 <_ZNSt8ios_base4InitD1Ev@plt>
    2a9e:	c9                   	leaveq 
    2a9f:	c3                   	retq   

0000000000002aa0 <_Z7saySth1v>:
    2aa0:	55                   	push   %rbp
    2aa1:	48 89 e5             	mov    %rsp,%rbp
    2aa4:	48 8d 35 cb 13 00 00 	lea    5067(%rip),%rsi        # 3e76 <_fini+0xe>
    2aab:	48 8b 3d 56 27 20 00 	mov    2107222(%rip),%rdi        # 205208 <_DYNAMIC+0x1c8>
    2ab2:	e8 39 fb ff ff       	callq  25f0 <_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@plt>
    2ab7:	48 89 c7             	mov    %rax,%rdi
    2aba:	48 8b 35 5f 27 20 00 	mov    2107231(%rip),%rsi        # 205220 <_DYNAMIC+0x1e0>
    2ac1:	e8 4a fd ff ff       	callq  2810 <_ZNSolsEPFRSoS_E@plt>
    2ac6:	e8 f5 fa ff ff       	callq  25c0 <_Z5hellov@plt>
    2acb:	b8 01 00 00 00       	mov    $0x1,%eax
    2ad0:	c9                   	leaveq 
    2ad1:	c3                   	retq   
    2ad2:	90                   	nop    
    2ad3:	90                   	nop    

0000000000002ad4 <_Z41__static_initialization_and_destruction_0ii>:
    2ad4:	55                   	push   %rbp
    2ad5:	48 89 e5             	mov    %rsp,%rbp
    2ad8:	53                   	push   %rbx
    2ad9:	48 83 ec 38          	sub    $0x38,%rsp
    2add:	89 7d cc             	mov    %edi,0xffffffffffffffcc(%rbp)
    2ae0:	89 75 c8             	mov    %esi,0xffffffffffffffc8(%rbp)
    2ae3:	83 7d cc 01          	cmpl   $0x1,0xffffffffffffffcc(%rbp)
    2ae7:	0f 85 51 01 00 00    	jne    2c3e <_Z41__static_initialization_and_destruction_0ii+0x16a>
    2aed:	81 7d c8 ff ff 00 00 	cmpl   $0xffff,0xffffffffffffffc8(%rbp)
    2af4:	0f 85 44 01 00 00    	jne    2c3e <_Z41__static_initialization_and_destruction_0ii+0x16a>
    2afa:	48 8d 3d 07 2a 20 00 	lea    2107911(%rip),%rdi        # 205508 <_ZSt8__ioinit>
    2b01:	e8 0a fa ff ff       	callq  2510 <_ZNSt8ios_base4InitC1Ev@plt>
    2b06:	48 8b 15 03 27 20 00 	mov    2107139(%rip),%rdx        # 205210 <_DYNAMIC+0x1d0>
    2b0d:	be 00 00 00 00       	mov    $0x0,%esi
    2b12:	48 8d 3d 77 01 00 00 	lea    375(%rip),%rdi        # 2c90 <__tcf_0>
    2b19:	e8 62 fa ff ff       	callq  2580 <__cxa_atexit@plt>
    2b1e:	48 8d 7d df          	lea    0xffffffffffffffdf(%rbp),%rdi
    2b22:	e8 69 fd ff ff       	callq  2890 <_ZNSaIcEC1Ev@plt>
    2b27:	48 8d 55 df          	lea    0xffffffffffffffdf(%rbp),%rdx
    2b2b:	48 8d 7d d0          	lea    0xffffffffffffffd0(%rbp),%rdi
    2b2f:	48 8d 35 5b 13 00 00 	lea    4955(%rip),%rsi        # 3e91 <_fini+0x29>
    2b36:	e8 85 fb ff ff       	callq  26c0 <_ZNSsC1EPKcRKSaIcE@plt>
    2b3b:	48 8d 75 d0          	lea    0xffffffffffffffd0(%rbp),%rsi
    2b3f:	48 8d 3d ca 29 20 00 	lea    2107850(%rip),%rdi        # 205510 <sObj>
    2b46:	e8 b5 fd ff ff       	callq  2900 <_ZN4TestC1ERKSs@plt>
    2b4b:	48 8d 7d d0          	lea    0xffffffffffffffd0(%rbp),%rdi
    2b4f:	e8 bc fa ff ff       	callq  2610 <_ZNSsD1Ev@plt>
    2b54:	eb 17                	jmp    2b6d <_Z41__static_initialization_and_destruction_0ii+0x99>
    2b56:	48 89 45 c0          	mov    %rax,0xffffffffffffffc0(%rbp)
    2b5a:	48 8b 5d c0          	mov    0xffffffffffffffc0(%rbp),%rbx
    2b5e:	48 8d 7d d0          	lea    0xffffffffffffffd0(%rbp),%rdi
    2b62:	e8 a9 fa ff ff       	callq  2610 <_ZNSsD1Ev@plt>
    2b67:	48 89 5d c0          	mov    %rbx,0xffffffffffffffc0(%rbp)
    2b6b:	eb 44                	jmp    2bb1 <_Z41__static_initialization_and_destruction_0ii+0xdd>
    2b6d:	48 8d 7d df          	lea    0xffffffffffffffdf(%rbp),%rdi
    2b71:	e8 5a fc ff ff       	callq  27d0 <_ZNSaIcED1Ev@plt>
    2b76:	48 8b 15 93 26 20 00 	mov    2107027(%rip),%rdx        # 205210 <_DYNAMIC+0x1d0>
    2b7d:	be 00 00 00 00       	mov    $0x0,%esi
    2b82:	48 8d 3d ed 00 00 00 	lea    237(%rip),%rdi        # 2c76 <__tcf_1>
    2b89:	e8 f2 f9 ff ff       	callq  2580 <__cxa_atexit@plt>
    2b8e:	48 8d 7d ef          	lea    0xffffffffffffffef(%rbp),%rdi
    2b92:	e8 f9 fc ff ff       	callq  2890 <_ZNSaIcEC1Ev@plt>
    2b97:	48 8d 55 ef          	lea    0xffffffffffffffef(%rbp),%rdx
    2b9b:	48 8d 7d e0          	lea    0xffffffffffffffe0(%rbp),%rdi
    2b9f:	48 8d 35 f0 12 00 00 	lea    4848(%rip),%rsi        # 3e96 <_fini+0x2e>
    2ba6:	e8 15 fb ff ff       	callq  26c0 <_ZNSsC1EPKcRKSaIcE@plt>
    2bab:	eb 1e                	jmp    2bcb <_Z41__static_initialization_and_destruction_0ii+0xf7>
    2bad:	48 89 45 c0          	mov    %rax,0xffffffffffffffc0(%rbp)
    2bb1:	48 8b 5d c0          	mov    0xffffffffffffffc0(%rbp),%rbx
    2bb5:	48 8d 7d df          	lea    0xffffffffffffffdf(%rbp),%rdi
    2bb9:	e8 12 fc ff ff       	callq  27d0 <_ZNSaIcED1Ev@plt>
    2bbe:	48 89 5d c0          	mov    %rbx,0xffffffffffffffc0(%rbp)
    2bc2:	48 8b 7d c0          	mov    0xffffffffffffffc0(%rbp),%rdi
    2bc6:	e8 f5 fc ff ff       	callq  28c0 <_Unwind_Resume@plt>
    2bcb:	48 8d 75 e0          	lea    0xffffffffffffffe0(%rbp),%rsi
    2bcf:	48 8b 3d 42 26 20 00 	mov    2106946(%rip),%rdi        # 205218 <_DYNAMIC+0x1d8>
    2bd6:	e8 25 fd ff ff       	callq  2900 <_ZN4TestC1ERKSs@plt>
    2bdb:	48 8d 7d e0          	lea    0xffffffffffffffe0(%rbp),%rdi
    2bdf:	e8 2c fa ff ff       	callq  2610 <_ZNSsD1Ev@plt>
    2be4:	eb 17                	jmp    2bfd <_Z41__static_initialization_and_destruction_0ii+0x129>
    2be6:	48 89 45 c0          	mov    %rax,0xffffffffffffffc0(%rbp)
    2bea:	48 8b 5d c0          	mov    0xffffffffffffffc0(%rbp),%rbx
    2bee:	48 8d 7d e0          	lea    0xffffffffffffffe0(%rbp),%rdi
    2bf2:	e8 19 fa ff ff       	callq  2610 <_ZNSsD1Ev@plt>
    2bf7:	48 89 5d c0          	mov    %rbx,0xffffffffffffffc0(%rbp)
    2bfb:	eb 27                	jmp    2c24 <_Z41__static_initialization_and_destruction_0ii+0x150>
    2bfd:	48 8d 7d ef          	lea    0xffffffffffffffef(%rbp),%rdi
    2c01:	e8 ca fb ff ff       	callq  27d0 <_ZNSaIcED1Ev@plt>
    2c06:	48 8b 15 03 26 20 00 	mov    2106883(%rip),%rdx        # 205210 <_DYNAMIC+0x1d0>
    2c0d:	be 00 00 00 00       	mov    $0x0,%esi
    2c12:	48 8d 3d 43 00 00 00 	lea    67(%rip),%rdi        # 2c5c <__tcf_2>
    2c19:	e8 62 f9 ff ff       	callq  2580 <__cxa_atexit@plt>
    2c1e:	eb 1e                	jmp    2c3e <_Z41__static_initialization_and_destruction_0ii+0x16a>
    2c20:	48 89 45 c0          	mov    %rax,0xffffffffffffffc0(%rbp)
    2c24:	48 8b 5d c0          	mov    0xffffffffffffffc0(%rbp),%rbx
    2c28:	48 8d 7d ef          	lea    0xffffffffffffffef(%rbp),%rdi
    2c2c:	e8 9f fb ff ff       	callq  27d0 <_ZNSaIcED1Ev@plt>
    2c31:	48 89 5d c0          	mov    %rbx,0xffffffffffffffc0(%rbp)
    2c35:	48 8b 7d c0          	mov    0xffffffffffffffc0(%rbp),%rdi
    2c39:	e8 82 fc ff ff       	callq  28c0 <_Unwind_Resume@plt>
    2c3e:	48 83 c4 38          	add    $0x38,%rsp
    2c42:	5b                   	pop    %rbx
    2c43:	c9                   	leaveq 
    2c44:	c3                   	retq   
    2c45:	90                   	nop    

0000000000002c46 <_GLOBAL__I_gObj>:
    2c46:	55                   	push   %rbp
    2c47:	48 89 e5             	mov    %rsp,%rbp
    2c4a:	be ff ff 00 00       	mov    $0xffff,%esi
    2c4f:	bf 01 00 00 00       	mov    $0x1,%edi
    2c54:	e8 7b fe ff ff       	callq  2ad4 <_Z41__static_initialization_and_destruction_0ii>
    2c59:	c9                   	leaveq 
    2c5a:	c3                   	retq   
    2c5b:	90                   	nop    

0000000000002c5c <__tcf_2>:
    2c5c:	55                   	push   %rbp
    2c5d:	48 89 e5             	mov    %rsp,%rbp
    2c60:	48 83 ec 10          	sub    $0x10,%rsp
    2c64:	48 89 7d f8          	mov    %rdi,0xfffffffffffffff8(%rbp)
    2c68:	48 8b 3d a9 25 20 00 	mov    2106793(%rip),%rdi        # 205218 <_DYNAMIC+0x1d8>
    2c6f:	e8 1c fb ff ff       	callq  2790 <_ZN4TestD1Ev@plt>
    2c74:	c9                   	leaveq 
    2c75:	c3                   	retq   

0000000000002c76 <__tcf_1>:
    2c76:	55                   	push   %rbp
    2c77:	48 89 e5             	mov    %rsp,%rbp
    2c7a:	48 83 ec 10          	sub    $0x10,%rsp
    2c7e:	48 89 7d f8          	mov    %rdi,0xfffffffffffffff8(%rbp)
    2c82:	48 8d 3d 87 28 20 00 	lea    2107527(%rip),%rdi        # 205510 <sObj>
    2c89:	e8 02 fb ff ff       	callq  2790 <_ZN4TestD1Ev@plt>
    2c8e:	c9                   	leaveq 
    2c8f:	c3                   	retq   

0000000000002c90 <__tcf_0>:
    2c90:	55                   	push   %rbp
    2c91:	48 89 e5             	mov    %rsp,%rbp
    2c94:	48 83 ec 10          	sub    $0x10,%rsp
    2c98:	48 89 7d f8          	mov    %rdi,0xfffffffffffffff8(%rbp)
    2c9c:	48 8d 3d 65 28 20 00 	lea    2107493(%rip),%rdi        # 205508 <_ZSt8__ioinit>
    2ca3:	e8 38 f9 ff ff       	callq  25e0 <_ZNSt8ios_base4InitD1Ev@plt>
    2ca8:	c9                   	leaveq 
    2ca9:	c3                   	retq   

0000000000002caa <_Z5hellov>:
    2caa:	55                   	push   %rbp
    2cab:	48 89 e5             	mov    %rsp,%rbp
    2cae:	53                   	push   %rbx
    2caf:	48 83 ec 38          	sub    $0x38,%rsp
    2cb3:	48 8d 35 fd 11 00 00 	lea    4605(%rip),%rsi        # 3eb7 <_fini+0x4f>
    2cba:	48 8b 3d 47 25 20 00 	mov    2106695(%rip),%rdi        # 205208 <_DYNAMIC+0x1c8>
    2cc1:	e8 2a f9 ff ff       	callq  25f0 <_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@plt>
    2cc6:	48 89 c7             	mov    %rax,%rdi
    2cc9:	48 8b 35 50 25 20 00 	mov    2106704(%rip),%rsi        # 205220 <_DYNAMIC+0x1e0>
    2cd0:	e8 3b fb ff ff       	callq  2810 <_ZNSolsEPFRSoS_E@plt>
    2cd5:	48 8d 7d df          	lea    0xffffffffffffffdf(%rbp),%rdi
    2cd9:	e8 b2 fb ff ff       	callq  2890 <_ZNSaIcEC1Ev@plt>
    2cde:	48 8d 55 df          	lea    0xffffffffffffffdf(%rbp),%rdx
    2ce2:	48 8d 7d d0          	lea    0xffffffffffffffd0(%rbp),%rdi
    2ce6:	48 8d 35 e0 11 00 00 	lea    4576(%rip),%rsi        # 3ecd <_fini+0x65>
    2ced:	e8 ce f9 ff ff       	callq  26c0 <_ZNSsC1EPKcRKSaIcE@plt>
    2cf2:	48 8d 75 d0          	lea    0xffffffffffffffd0(%rbp),%rsi
    2cf6:	48 8b 3d 1b 25 20 00 	mov    2106651(%rip),%rdi        # 205218 <_DYNAMIC+0x1d8>
    2cfd:	e8 3e fa ff ff       	callq  2740 <_ZN4Test6addSthERKSs@plt>
    2d02:	48 8d 7d d0          	lea    0xffffffffffffffd0(%rbp),%rdi
    2d06:	e8 05 f9 ff ff       	callq  2610 <_ZNSsD1Ev@plt>
    2d0b:	eb 17                	jmp    2d24 <_Z5hellov+0x7a>
    2d0d:	48 89 45 c8          	mov    %rax,0xffffffffffffffc8(%rbp)
    2d11:	48 8b 5d c8          	mov    0xffffffffffffffc8(%rbp),%rbx
    2d15:	48 8d 7d d0          	lea    0xffffffffffffffd0(%rbp),%rdi
    2d19:	e8 f2 f8 ff ff       	callq  2610 <_ZNSsD1Ev@plt>
    2d1e:	48 89 5d c8          	mov    %rbx,0xffffffffffffffc8(%rbp)
    2d22:	eb 2c                	jmp    2d50 <_Z5hellov+0xa6>
    2d24:	48 8d 7d df          	lea    0xffffffffffffffdf(%rbp),%rdi
    2d28:	e8 a3 fa ff ff       	callq  27d0 <_ZNSaIcED1Ev@plt>
    2d2d:	48 8d 7d ef          	lea    0xffffffffffffffef(%rbp),%rdi
    2d31:	e8 5a fb ff ff       	callq  2890 <_ZNSaIcEC1Ev@plt>
    2d36:	48 8d 55 ef          	lea    0xffffffffffffffef(%rbp),%rdx
    2d3a:	48 8d 7d e0          	lea    0xffffffffffffffe0(%rbp),%rdi
    2d3e:	48 8d 35 88 11 00 00 	lea    4488(%rip),%rsi        # 3ecd <_fini+0x65>
    2d45:	e8 76 f9 ff ff       	callq  26c0 <_ZNSsC1EPKcRKSaIcE@plt>
    2d4a:	eb 1e                	jmp    2d6a <_Z5hellov+0xc0>
    2d4c:	48 89 45 c8          	mov    %rax,0xffffffffffffffc8(%rbp)
    2d50:	48 8b 5d c8          	mov    0xffffffffffffffc8(%rbp),%rbx
    2d54:	48 8d 7d df          	lea    0xffffffffffffffdf(%rbp),%rdi
    2d58:	e8 73 fa ff ff       	callq  27d0 <_ZNSaIcED1Ev@plt>
    2d5d:	48 89 5d c8          	mov    %rbx,0xffffffffffffffc8(%rbp)
    2d61:	48 8b 7d c8          	mov    0xffffffffffffffc8(%rbp),%rdi
    2d65:	e8 56 fb ff ff       	callq  28c0 <_Unwind_Resume@plt>
    2d6a:	48 8d 75 e0          	lea    0xffffffffffffffe0(%rbp),%rsi
    2d6e:	48 8d 3d 9b 27 20 00 	lea    2107291(%rip),%rdi        # 205510 <sObj>
    2d75:	e8 c6 f9 ff ff       	callq  2740 <_ZN4Test6addSthERKSs@plt>
    2d7a:	48 8d 7d e0          	lea    0xffffffffffffffe0(%rbp),%rdi
    2d7e:	e8 8d f8 ff ff       	callq  2610 <_ZNSsD1Ev@plt>
    2d83:	eb 1a                	jmp    2d9f <_Z5hellov+0xf5>
    2d85:	48 89 45 c8          	mov    %rax,0xffffffffffffffc8(%rbp)
    2d89:	48 8b 5d c8          	mov    0xffffffffffffffc8(%rbp),%rbx
    2d8d:	48 8d 7d e0          	lea    0xffffffffffffffe0(%rbp),%rdi
    2d91:	e8 7a f8 ff ff       	callq  2610 <_ZNSsD1Ev@plt>
    2d96:	48 89 5d c8          	mov    %rbx,0xffffffffffffffc8(%rbp)
    2d9a:	e9 e9 00 00 00       	jmpq   2e88 <_Z5hellov+0x1de>
    2d9f:	48 8d 7d ef          	lea    0xffffffffffffffef(%rbp),%rdi
    2da3:	e8 28 fa ff ff       	callq  27d0 <_ZNSaIcED1Ev@plt>
    2da8:	48 8d 35 23 11 00 00 	lea    4387(%rip),%rsi        # 3ed2 <_fini+0x6a>
    2daf:	48 8b 3d 52 24 20 00 	mov    2106450(%rip),%rdi        # 205208 <_DYNAMIC+0x1c8>
    2db6:	e8 35 f8 ff ff       	callq  25f0 <_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@plt>
    2dbb:	48 89 c7             	mov    %rax,%rdi
    2dbe:	48 8b 35 53 24 20 00 	mov    2106451(%rip),%rsi        # 205218 <_DYNAMIC+0x1d8>
    2dc5:	e8 86 f8 ff ff       	callq  2650 <_ZNSolsEPKv@plt>
    2dca:	48 89 c7             	mov    %rax,%rdi
    2dcd:	48 8b 35 4c 24 20 00 	mov    2106444(%rip),%rsi        # 205220 <_DYNAMIC+0x1e0>
    2dd4:	e8 37 fa ff ff       	callq  2810 <_ZNSolsEPFRSoS_E@plt>
    2dd9:	48 8b 3d 38 24 20 00 	mov    2106424(%rip),%rdi        # 205218 <_DYNAMIC+0x1d8>
    2de0:	e8 3b f9 ff ff       	callq  2720 <_ZNK4Test8getCountEv@plt>
    2de5:	48 89 c3             	mov    %rax,%rbx
    2de8:	48 8d 35 e3 10 00 00 	lea    4323(%rip),%rsi        # 3ed2 <_fini+0x6a>
    2def:	48 8b 3d 12 24 20 00 	mov    2106386(%rip),%rdi        # 205208 <_DYNAMIC+0x1c8>
    2df6:	e8 f5 f7 ff ff       	callq  25f0 <_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@plt>
    2dfb:	48 89 c7             	mov    %rax,%rdi
    2dfe:	48 89 de             	mov    %rbx,%rsi
    2e01:	e8 9a f8 ff ff       	callq  26a0 <_ZNSolsEm@plt>
    2e06:	48 89 c7             	mov    %rax,%rdi
    2e09:	48 8b 35 10 24 20 00 	mov    2106384(%rip),%rsi        # 205220 <_DYNAMIC+0x1e0>
    2e10:	e8 fb f9 ff ff       	callq  2810 <_ZNSolsEPFRSoS_E@plt>
    2e15:	48 8d 35 be 10 00 00 	lea    4286(%rip),%rsi        # 3eda <_fini+0x72>
    2e1c:	48 8b 3d e5 23 20 00 	mov    2106341(%rip),%rdi        # 205208 <_DYNAMIC+0x1c8>
    2e23:	e8 c8 f7 ff ff       	callq  25f0 <_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@plt>
    2e28:	48 89 c7             	mov    %rax,%rdi
    2e2b:	48 8d 35 de 26 20 00 	lea    2107102(%rip),%rsi        # 205510 <sObj>
    2e32:	e8 19 f8 ff ff       	callq  2650 <_ZNSolsEPKv@plt>
    2e37:	48 89 c7             	mov    %rax,%rdi
    2e3a:	48 8b 35 df 23 20 00 	mov    2106335(%rip),%rsi        # 205220 <_DYNAMIC+0x1e0>
    2e41:	e8 ca f9 ff ff       	callq  2810 <_ZNSolsEPFRSoS_E@plt>
    2e46:	48 8d 3d c3 26 20 00 	lea    2107075(%rip),%rdi        # 205510 <sObj>
    2e4d:	e8 ce f8 ff ff       	callq  2720 <_ZNK4Test8getCountEv@plt>
    2e52:	48 89 c3             	mov    %rax,%rbx
    2e55:	48 8d 35 7e 10 00 00 	lea    4222(%rip),%rsi        # 3eda <_fini+0x72>
    2e5c:	48 8b 3d a5 23 20 00 	mov    2106277(%rip),%rdi        # 205208 <_DYNAMIC+0x1c8>
    2e63:	e8 88 f7 ff ff       	callq  25f0 <_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@plt>
    2e68:	48 89 c7             	mov    %rax,%rdi
    2e6b:	48 89 de             	mov    %rbx,%rsi
    2e6e:	e8 2d f8 ff ff       	callq  26a0 <_ZNSolsEm@plt>
    2e73:	48 89 c7             	mov    %rax,%rdi
    2e76:	48 8b 35 a3 23 20 00 	mov    2106275(%rip),%rsi        # 205220 <_DYNAMIC+0x1e0>
    2e7d:	e8 8e f9 ff ff       	callq  2810 <_ZNSolsEPFRSoS_E@plt>
    2e82:	eb 1e                	jmp    2ea2 <_Z5hellov+0x1f8>
    2e84:	48 89 45 c8          	mov    %rax,0xffffffffffffffc8(%rbp)
    2e88:	48 8b 5d c8          	mov    0xffffffffffffffc8(%rbp),%rbx
    2e8c:	48 8d 7d ef          	lea    0xffffffffffffffef(%rbp),%rdi
    2e90:	e8 3b f9 ff ff       	callq  27d0 <_ZNSaIcED1Ev@plt>
    2e95:	48 89 5d c8          	mov    %rbx,0xffffffffffffffc8(%rbp)
    2e99:	48 8b 7d c8          	mov    0xffffffffffffffc8(%rbp),%rdi
    2e9d:	e8 1e fa ff ff       	callq  28c0 <_Unwind_Resume@plt>
    2ea2:	48 83 c4 38          	add    $0x38,%rsp
    2ea6:	5b                   	pop    %rbx
    2ea7:	c9                   	leaveq 
    2ea8:	c3                   	retq   
    2ea9:	90                   	nop    

0000000000002eaa <_ZnwmPv>:
    2eaa:	55                   	push   %rbp
    2eab:	48 89 e5             	mov    %rsp,%rbp
    2eae:	48 89 7d f8          	mov    %rdi,0xfffffffffffffff8(%rbp)
    2eb2:	48 89 75 f0          	mov    %rsi,0xfffffffffffffff0(%rbp)
    2eb6:	48 8b 45 f0          	mov    0xfffffffffffffff0(%rbp),%rax
    2eba:	c9                   	leaveq 
    2ebb:	c3                   	retq   

0000000000002ebc <_ZdlPvS_>:
    2ebc:	55                   	push   %rbp
    2ebd:	48 89 e5             	mov    %rsp,%rbp
    2ec0:	48 89 7d f8          	mov    %rdi,0xfffffffffffffff8(%rbp)
    2ec4:	48 89 75 f0          	mov    %rsi,0xfffffffffffffff0(%rbp)
    2ec8:	c9                   	leaveq 
    2ec9:	c3                   	retq   

0000000000002eca <_ZN9__gnu_cxx13new_allocatorISsEC2Ev>:
    2eca:	55                   	push   %rbp
    2ecb:	48 89 e5             	mov    %rsp,%rbp
    2ece:	48 89 7d f8          	mov    %rdi,0xfffffffffffffff8(%rbp)
    2ed2:	c9                   	leaveq 
    2ed3:	c3                   	retq   

0000000000002ed4 <_ZNSaISsEC1Ev>:
    2ed4:	55                   	push   %rbp
    2ed5:	48 89 e5             	mov    %rsp,%rbp
    2ed8:	48 83 ec 10          	sub    $0x10,%rsp
    2edc:	48 89 7d f8          	mov    %rdi,0xfffffffffffffff8(%rbp)
    2ee0:	48 8b 7d f8          	mov    0xfffffffffffffff8(%rbp),%rdi
    2ee4:	e8 37 fa ff ff       	callq  2920 <_ZN9__gnu_cxx13new_allocatorISsEC2Ev@plt>
    2ee9:	c9                   	leaveq 
    2eea:	c3                   	retq   
    2eeb:	90                   	nop    

0000000000002eec <_ZN9__gnu_cxx13new_allocatorISsED2Ev>:
    2eec:	55                   	push   %rbp
    2eed:	48 89 e5             	mov    %rsp,%rbp
    2ef0:	48 89 7d f8          	mov    %rdi,0xfffffffffffffff8(%rbp)
    2ef4:	c9                   	leaveq 
    2ef5:	c3                   	retq   

0000000000002ef6 <_ZNSaISsED1Ev>:
    2ef6:	55                   	push   %rbp
    2ef7:	48 89 e5             	mov    %rsp,%rbp
    2efa:	48 83 ec 10          	sub    $0x10,%rsp
    2efe:	48 89 7d f8          	mov    %rdi,0xfffffffffffffff8(%rbp)
    2f02:	48 8b 7d f8          	mov    0xfffffffffffffff8(%rbp),%rdi
    2f06:	e8 25 f7 ff ff       	callq  2630 <_ZN9__gnu_cxx13new_allocatorISsED2Ev@plt>
    2f0b:	c9                   	leaveq 
    2f0c:	c3                   	retq   
    2f0d:	90                   	nop    

0000000000002f0e <_ZNSaISsED2Ev>:
    2f0e:	55                   	push   %rbp
    2f0f:	48 89 e5             	mov    %rsp,%rbp
    2f12:	48 83 ec 10          	sub    $0x10,%rsp
    2f16:	48 89 7d f8          	mov    %rdi,0xfffffffffffffff8(%rbp)
    2f1a:	48 8b 7d f8          	mov    0xfffffffffffffff8(%rbp),%rdi
    2f1e:	e8 0d f7 ff ff       	callq  2630 <_ZN9__gnu_cxx13new_allocatorISsED2Ev@plt>
    2f23:	c9                   	leaveq 
    2f24:	c3                   	retq   
    2f25:	90                   	nop    

0000000000002f26 <_ZN9__gnu_cxx13new_allocatorISsEC2ERKS1_>:
    2f26:	55                   	push   %rbp
    2f27:	48 89 e5             	mov    %rsp,%rbp
    2f2a:	48 89 7d f8          	mov    %rdi,0xfffffffffffffff8(%rbp)
    2f2e:	48 89 75 f0          	mov    %rsi,0xfffffffffffffff0(%rbp)
    2f32:	c9                   	leaveq 
    2f33:	c3                   	retq   

0000000000002f34 <_ZNSaISsEC2ERKS_>:
    2f34:	55                   	push   %rbp
    2f35:	48 89 e5             	mov    %rsp,%rbp
    2f38:	48 83 ec 10          	sub    $0x10,%rsp
    2f3c:	48 89 7d f8          	mov    %rdi,0xfffffffffffffff8(%rbp)
    2f40:	48 89 75 f0          	mov    %rsi,0xfffffffffffffff0(%rbp)
    2f44:	48 8b 75 f0          	mov    0xfffffffffffffff0(%rbp),%rsi
    2f48:	48 8b 7d f8          	mov    0xfffffffffffffff8(%rbp),%rdi
    2f4c:	e8 7f f9 ff ff       	callq  28d0 <_ZN9__gnu_cxx13new_allocatorISsEC2ERKS1_@plt>
    2f51:	c9                   	leaveq 
    2f52:	c3                   	retq   
    2f53:	90                   	nop    

0000000000002f54 <_ZNSaISsEC1ERKS_>:
    2f54:	55                   	push   %rbp
    2f55:	48 89 e5             	mov    %rsp,%rbp
    2f58:	48 83 ec 10          	sub    $0x10,%rsp
    2f5c:	48 89 7d f8          	mov    %rdi,0xfffffffffffffff8(%rbp)
    2f60:	48 89 75 f0          	mov    %rsi,0xfffffffffffffff0(%rbp)
    2f64:	48 8b 75 f0          	mov    0xfffffffffffffff0(%rbp),%rsi
    2f68:	48 8b 7d f8          	mov    0xfffffffffffffff8(%rbp),%rdi
    2f6c:	e8 5f f9 ff ff       	callq  28d0 <_ZN9__gnu_cxx13new_allocatorISsEC2ERKS1_@plt>
    2f71:	c9                   	leaveq 
    2f72:	c3                   	retq   
    2f73:	90                   	nop    

0000000000002f74 <_ZNSt12_Vector_baseISsSaISsEE12_Vector_implD1Ev>:
    2f74:	55                   	push   %rbp
    2f75:	48 89 e5             	mov    %rsp,%rbp
    2f78:	48 83 ec 10          	sub    $0x10,%rsp
    2f7c:	48 89 7d f8          	mov    %rdi,0xfffffffffffffff8(%rbp)
    2f80:	48 8b 7d f8          	mov    0xfffffffffffffff8(%rbp),%rdi
    2f84:	e8 27 f7 ff ff       	callq  26b0 <_ZNSaISsED2Ev@plt>
    2f89:	c9                   	leaveq 
    2f8a:	c3                   	retq   
    2f8b:	90                   	nop    

0000000000002f8c <_ZNSt12_Vector_baseISsSaISsEE19_M_get_Tp_allocatorEv>:
    2f8c:	55                   	push   %rbp
    2f8d:	48 89 e5             	mov    %rsp,%rbp
    2f90:	48 89 7d f8          	mov    %rdi,0xfffffffffffffff8(%rbp)
    2f94:	48 8b 45 f8          	mov    0xfffffffffffffff8(%rbp),%rax
    2f98:	c9                   	leaveq 
    2f99:	c3                   	retq   

0000000000002f9a <_ZNSt12_Vector_baseISsSaISsEE12_Vector_implC1ERKS0_>:
    2f9a:	55                   	push   %rbp
    2f9b:	48 89 e5             	mov    %rsp,%rbp
    2f9e:	48 83 ec 10          	sub    $0x10,%rsp
    2fa2:	48 89 7d f8          	mov    %rdi,0xfffffffffffffff8(%rbp)
    2fa6:	48 89 75 f0          	mov    %rsi,0xfffffffffffffff0(%rbp)
    2faa:	48 8b 7d f8          	mov    0xfffffffffffffff8(%rbp),%rdi
    2fae:	48 8b 75 f0          	mov    0xfffffffffffffff0(%rbp),%rsi
    2fb2:	e8 39 f9 ff ff       	callq  28f0 <_ZNSaISsEC2ERKS_@plt>
    2fb7:	48 8b 45 f8          	mov    0xfffffffffffffff8(%rbp),%rax
    2fbb:	48 c7 00 00 00 00 00 	movq   $0x0,(%rax)
    2fc2:	48 8b 45 f8          	mov    0xfffffffffffffff8(%rbp),%rax
    2fc6:	48 c7 40 08 00 00 00 	movq   $0x0,0x8(%rax)
    2fcd:	00 
    2fce:	48 8b 45 f8          	mov    0xfffffffffffffff8(%rbp),%rax
    2fd2:	48 c7 40 10 00 00 00 	movq   $0x0,0x10(%rax)
    2fd9:	00 
    2fda:	c9                   	leaveq 
    2fdb:	c3                   	retq   

0000000000002fdc <_ZNSt12_Vector_baseISsSaISsEEC2ERKS0_>:
    2fdc:	55                   	push   %rbp
    2fdd:	48 89 e5             	mov    %rsp,%rbp
    2fe0:	48 83 ec 10          	sub    $0x10,%rsp
    2fe4:	48 89 7d f8          	mov    %rdi,0xfffffffffffffff8(%rbp)
    2fe8:	48 89 75 f0          	mov    %rsi,0xfffffffffffffff0(%rbp)
    2fec:	48 8b 7d f8          	mov    0xfffffffffffffff8(%rbp),%rdi
    2ff0:	48 8b 75 f0          	mov    0xfffffffffffffff0(%rbp),%rsi
    2ff4:	e8 57 f8 ff ff       	callq  2850 <_ZNSt12_Vector_baseISsSaISsEE12_Vector_implC1ERKS0_@plt>
    2ff9:	c9                   	leaveq 
    2ffa:	c3                   	retq   
    2ffb:	90                   	nop    

0000000000002ffc <_ZNSt6vectorISsSaISsEEC1ERKS0_>:
    2ffc:	55                   	push   %rbp
    2ffd:	48 89 e5             	mov    %rsp,%rbp
    3000:	48 83 ec 10          	sub    $0x10,%rsp
    3004:	48 89 7d f8          	mov    %rdi,0xfffffffffffffff8(%rbp)
    3008:	48 89 75 f0          	mov    %rsi,0xfffffffffffffff0(%rbp)
    300c:	48 8b 7d f8          	mov    0xfffffffffffffff8(%rbp),%rdi
    3010:	48 8b 75 f0          	mov    0xfffffffffffffff0(%rbp),%rsi
    3014:	e8 a7 f4 ff ff       	callq  24c0 <_ZNSt12_Vector_baseISsSaISsEEC2ERKS0_@plt>
    3019:	c9                   	leaveq 
    301a:	c3                   	retq   
    301b:	90                   	nop    

000000000000301c <_ZN9__gnu_cxx17__normal_iteratorIPSsSt6vectorISsSaISsEEEC1ERKS1_>:
    301c:	55                   	push   %rbp
    301d:	48 89 e5             	mov    %rsp,%rbp
    3020:	48 89 7d f8          	mov    %rdi,0xfffffffffffffff8(%rbp)
    3024:	48 89 75 f0          	mov    %rsi,0xfffffffffffffff0(%rbp)
    3028:	48 8b 45 f0          	mov    0xfffffffffffffff0(%rbp),%rax
    302c:	48 8b 10             	mov    (%rax),%rdx
    302f:	48 8b 45 f8          	mov    0xfffffffffffffff8(%rbp),%rax
    3033:	48 89 10             	mov    %rdx,(%rax)
    3036:	c9                   	leaveq 
    3037:	c3                   	retq   

0000000000003038 <_ZNSt6vectorISsSaISsEE3endEv>:
    3038:	55                   	push   %rbp
    3039:	48 89 e5             	mov    %rsp,%rbp
    303c:	48 83 ec 20          	sub    $0x20,%rsp
    3040:	48 89 7d e8          	mov    %rdi,0xffffffffffffffe8(%rbp)
    3044:	48 8b 75 e8          	mov    0xffffffffffffffe8(%rbp),%rsi
    3048:	48 83 c6 08          	add    $0x8,%rsi
    304c:	48 8d 7d f0          	lea    0xfffffffffffffff0(%rbp),%rdi
    3050:	e8 2b f7 ff ff       	callq  2780 <_ZN9__gnu_cxx17__normal_iteratorIPSsSt6vectorISsSaISsEEEC1ERKS1_@plt>
    3055:	48 8b 45 f0          	mov    0xfffffffffffffff0(%rbp),%rax
    3059:	c9                   	leaveq 
    305a:	c3                   	retq   
    305b:	90                   	nop    

000000000000305c <_ZNK9__gnu_cxx17__normal_iteratorIPSsSt6vectorISsSaISsEEEdeEv>:
    305c:	55                   	push   %rbp
    305d:	48 89 e5             	mov    %rsp,%rbp
    3060:	48 89 7d f8          	mov    %rdi,0xfffffffffffffff8(%rbp)
    3064:	48 8b 45 f8          	mov    0xfffffffffffffff8(%rbp),%rax
    3068:	48 8b 00             	mov    (%rax),%rax
    306b:	c9                   	leaveq 
    306c:	c3                   	retq   
    306d:	90                   	nop    

000000000000306e <_ZNKSt6vectorISsSaISsEE8max_sizeEv>:
    306e:	55                   	push   %rbp
    306f:	48 89 e5             	mov    %rsp,%rbp
    3072:	48 89 7d f8          	mov    %rdi,0xfffffffffffffff8(%rbp)
    3076:	48 b8 ff ff ff ff ff 	mov    $0x1fffffffffffffff,%rax
    307d:	ff ff 1f 
    3080:	c9                   	leaveq 
    3081:	c3                   	retq   

0000000000003082 <_ZNK9__gnu_cxx17__normal_iteratorIPSsSt6vectorISsSaISsEEE4baseEv>:
    3082:	55                   	push   %rbp
    3083:	48 89 e5             	mov    %rsp,%rbp
    3086:	48 89 7d f8          	mov    %rdi,0xfffffffffffffff8(%rbp)
    308a:	48 8b 45 f8          	mov    0xfffffffffffffff8(%rbp),%rax
    308e:	c9                   	leaveq 
    308f:	c3                   	retq   

0000000000003090 <_ZN9__gnu_cxx17__normal_iteratorIPSsSt6vectorISsSaISsEEEppEv>:
    3090:	55                   	push   %rbp
    3091:	48 89 e5             	mov    %rsp,%rbp
    3094:	48 89 7d f8          	mov    %rdi,0xfffffffffffffff8(%rbp)
    3098:	48 8b 45 f8          	mov    0xfffffffffffffff8(%rbp),%rax
    309c:	48 8b 00             	mov    (%rax),%rax
    309f:	48 8d 50 08          	lea    0x8(%rax),%rdx
    30a3:	48 8b 45 f8          	mov    0xfffffffffffffff8(%rbp),%rax
    30a7:	48 89 10             	mov    %rdx,(%rax)
    30aa:	48 8b 45 f8          	mov    0xfffffffffffffff8(%rbp),%rax
    30ae:	c9                   	leaveq 
    30af:	c3                   	retq   

00000000000030b0 <_ZNSt6vectorISsSaISsEE5beginEv>:
    30b0:	55                   	push   %rbp
    30b1:	48 89 e5             	mov    %rsp,%rbp
    30b4:	48 83 ec 20          	sub    $0x20,%rsp
    30b8:	48 89 7d e8          	mov    %rdi,0xffffffffffffffe8(%rbp)
    30bc:	48 8b 75 e8          	mov    0xffffffffffffffe8(%rbp),%rsi
    30c0:	48 8d 7d f0          	lea    0xfffffffffffffff0(%rbp),%rdi
    30c4:	e8 b7 f6 ff ff       	callq  2780 <_ZN9__gnu_cxx17__normal_iteratorIPSsSt6vectorISsSaISsEEEC1ERKS1_@plt>
    30c9:	48 8b 45 f0          	mov    0xfffffffffffffff0(%rbp),%rax
    30cd:	c9                   	leaveq 
    30ce:	c3                   	retq   
    30cf:	90                   	nop    

00000000000030d0 <_ZN9__gnu_cxx17__normal_iteratorIPKSsSt6vectorISsSaISsEEEC1ERKS2_>:
    30d0:	55                   	push   %rbp
    30d1:	48 89 e5             	mov    %rsp,%rbp
    30d4:	48 89 7d f8          	mov    %rdi,0xfffffffffffffff8(%rbp)
    30d8:	48 89 75 f0          	mov    %rsi,0xfffffffffffffff0(%rbp)
    30dc:	48 8b 45 f0          	mov    0xfffffffffffffff0(%rbp),%rax
    30e0:	48 8b 10             	mov    (%rax),%rdx
    30e3:	48 8b 45 f8          	mov    0xfffffffffffffff8(%rbp),%rax
    30e7:	48 89 10             	mov    %rdx,(%rax)
    30ea:	c9                   	leaveq 
    30eb:	c3                   	retq   

00000000000030ec <_ZNKSt6vectorISsSaISsEE5beginEv>:
    30ec:	55                   	push   %rbp
    30ed:	48 89 e5             	mov    %rsp,%rbp
    30f0:	48 83 ec 20          	sub    $0x20,%rsp
    30f4:	48 89 7d e8          	mov    %rdi,0xffffffffffffffe8(%rbp)
    30f8:	48 8b 45 e8          	mov    0xffffffffffffffe8(%rbp),%rax
    30fc:	48 8b 00             	mov    (%rax),%rax
    30ff:	48 89 45 f8          	mov    %rax,0xfffffffffffffff8(%rbp)
    3103:	48 8d 75 f8          	lea    0xfffffffffffffff8(%rbp),%rsi
    3107:	48 8d 7d f0          	lea    0xfffffffffffffff0(%rbp),%rdi
    310b:	e8 a0 f3 ff ff       	callq  24b0 <_ZN9__gnu_cxx17__normal_iteratorIPKSsSt6vectorISsSaISsEEEC1ERKS2_@plt>
    3110:	48 8b 45 f0          	mov    0xfffffffffffffff0(%rbp),%rax
    3114:	c9                   	leaveq 
    3115:	c3                   	retq   

0000000000003116 <_ZNKSt6vectorISsSaISsEE3endEv>:
    3116:	55                   	push   %rbp
    3117:	48 89 e5             	mov    %rsp,%rbp
    311a:	48 83 ec 20          	sub    $0x20,%rsp
    311e:	48 89 7d e8          	mov    %rdi,0xffffffffffffffe8(%rbp)
    3122:	48 8b 45 e8          	mov    0xffffffffffffffe8(%rbp),%rax
    3126:	48 8b 40 08          	mov    0x8(%rax),%rax
    312a:	48 89 45 f8          	mov    %rax,0xfffffffffffffff8(%rbp)
    312e:	48 8d 75 f8          	lea    0xfffffffffffffff8(%rbp),%rsi
    3132:	48 8d 7d f0          	lea    0xfffffffffffffff0(%rbp),%rdi
    3136:	e8 75 f3 ff ff       	callq  24b0 <_ZN9__gnu_cxx17__normal_iteratorIPKSsSt6vectorISsSaISsEEEC1ERKS2_@plt>
    313b:	48 8b 45 f0          	mov    0xfffffffffffffff0(%rbp),%rax
    313f:	c9                   	leaveq 
    3140:	c3                   	retq   
    3141:	90                   	nop    

0000000000003142 <_ZNK9__gnu_cxx17__normal_iteratorIPKSsSt6vectorISsSaISsEEE4baseEv>:
    3142:	55                   	push   %rbp
    3143:	48 89 e5             	mov    %rsp,%rbp
    3146:	48 89 7d f8          	mov    %rdi,0xfffffffffffffff8(%rbp)
    314a:	48 8b 45 f8          	mov    0xfffffffffffffff8(%rbp),%rax
    314e:	c9                   	leaveq 
    314f:	c3                   	retq   

0000000000003150 <_ZN9__gnu_cxxmiIPKSsS2_St6vectorISsSaISsEEEENS_17__normal_iteratorIT_T1_E15difference_typeERKS9_RKNS6_IT0_S8_EE>:
    3150:	55                   	push   %rbp
    3151:	48 89 e5             	mov    %rsp,%rbp
    3154:	53                   	push   %rbx
    3155:	48 83 ec 18          	sub    $0x18,%rsp
    3159:	48 89 7d f0          	mov    %rdi,0xfffffffffffffff0(%rbp)
    315d:	48 89 75 e8          	mov    %rsi,0xffffffffffffffe8(%rbp)
    3161:	48 8b 7d f0          	mov    0xfffffffffffffff0(%rbp),%rdi
    3165:	e8 a6 f5 ff ff       	callq  2710 <_ZNK9__gnu_cxx17__normal_iteratorIPKSsSt6vectorISsSaISsEEE4baseEv@plt>
    316a:	48 8b 00             	mov    (%rax),%rax
    316d:	48 89 c3             	mov    %rax,%rbx
    3170:	48 8b 7d e8          	mov    0xffffffffffffffe8(%rbp),%rdi
    3174:	e8 97 f5 ff ff       	callq  2710 <_ZNK9__gnu_cxx17__normal_iteratorIPKSsSt6vectorISsSaISsEEE4baseEv@plt>
    3179:	48 8b 00             	mov    (%rax),%rax
    317c:	48 89 da             	mov    %rbx,%rdx
    317f:	48 29 c2             	sub    %rax,%rdx
    3182:	48 89 d0             	mov    %rdx,%rax
    3185:	48 c1 f8 03          	sar    $0x3,%rax
    3189:	48 83 c4 18          	add    $0x18,%rsp
    318d:	5b                   	pop    %rbx
    318e:	c9                   	leaveq 
    318f:	c3                   	retq   

0000000000003190 <_ZNKSt6vectorISsSaISsEE4sizeEv>:
    3190:	55                   	push   %rbp
    3191:	48 89 e5             	mov    %rsp,%rbp
    3194:	48 83 ec 30          	sub    $0x30,%rsp
    3198:	48 89 7d d8          	mov    %rdi,0xffffffffffffffd8(%rbp)
    319c:	48 8b 7d d8          	mov    0xffffffffffffffd8(%rbp),%rdi
    31a0:	e8 4b f3 ff ff       	callq  24f0 <_ZNKSt6vectorISsSaISsEE5beginEv@plt>
    31a5:	48 89 45 e0          	mov    %rax,0xffffffffffffffe0(%rbp)
    31a9:	48 8b 7d d8          	mov    0xffffffffffffffd8(%rbp),%rdi
    31ad:	e8 ae f4 ff ff       	callq  2660 <_ZNKSt6vectorISsSaISsEE3endEv@plt>
    31b2:	48 89 45 f0          	mov    %rax,0xfffffffffffffff0(%rbp)
    31b6:	48 8d 75 e0          	lea    0xffffffffffffffe0(%rbp),%rsi
    31ba:	48 8d 7d f0          	lea    0xfffffffffffffff0(%rbp),%rdi
    31be:	e8 1d f7 ff ff       	callq  28e0 <_ZN9__gnu_cxxmiIPKSsS2_St6vectorISsSaISsEEEENS_17__normal_iteratorIT_T1_E15difference_typeERKS9_RKNS6_IT0_S8_EE@plt>
    31c3:	c9                   	leaveq 
    31c4:	c3                   	retq   
    31c5:	90                   	nop    

00000000000031c6 <_ZNK4Test8getCountEv>:
    31c6:	55                   	push   %rbp
    31c7:	48 89 e5             	mov    %rsp,%rbp
    31ca:	48 83 ec 10          	sub    $0x10,%rsp
    31ce:	48 89 7d f8          	mov    %rdi,0xfffffffffffffff8(%rbp)
    31d2:	48 8b 7d f8          	mov    0xfffffffffffffff8(%rbp),%rdi
    31d6:	e8 25 f5 ff ff       	callq  2700 <_ZNKSt6vectorISsSaISsEE4sizeEv@plt>
    31db:	c9                   	leaveq 
    31dc:	c3                   	retq   
    31dd:	90                   	nop    

00000000000031de <_ZSt8_DestroyISsEvPT_>:
    31de:	55                   	push   %rbp
    31df:	48 89 e5             	mov    %rsp,%rbp
    31e2:	48 83 ec 10          	sub    $0x10,%rsp
    31e6:	48 89 7d f8          	mov    %rdi,0xfffffffffffffff8(%rbp)
    31ea:	48 8b 7d f8          	mov    0xfffffffffffffff8(%rbp),%rdi
    31ee:	e8 1d f4 ff ff       	callq  2610 <_ZNSsD1Ev@plt>
    31f3:	c9                   	leaveq 
    31f4:	c3                   	retq   
    31f5:	90                   	nop    

00000000000031f6 <_ZSt13__destroy_auxIPSsEvT_S1_12__false_type>:
    31f6:	55                   	push   %rbp
    31f7:	48 89 e5             	mov    %rsp,%rbp
    31fa:	48 83 ec 10          	sub    $0x10,%rsp
    31fe:	48 89 7d f8          	mov    %rdi,0xfffffffffffffff8(%rbp)
    3202:	48 89 75 f0          	mov    %rsi,0xfffffffffffffff0(%rbp)
    3206:	eb 0e                	jmp    3216 <_ZSt13__destroy_auxIPSsEvT_S1_12__false_type+0x20>
    3208:	48 8b 7d f8          	mov    0xfffffffffffffff8(%rbp),%rdi
    320c:	e8 2f f3 ff ff       	callq  2540 <_ZSt8_DestroyISsEvPT_@plt>
    3211:	48 83 45 f8 08       	addq   $0x8,0xfffffffffffffff8(%rbp)
    3216:	48 8b 45 f8          	mov    0xfffffffffffffff8(%rbp),%rax
    321a:	48 3b 45 f0          	cmp    0xfffffffffffffff0(%rbp),%rax
    321e:	75 e8                	jne    3208 <_ZSt13__destroy_auxIPSsEvT_S1_12__false_type+0x12>
    3220:	c9                   	leaveq 
    3221:	c3                   	retq   

0000000000003222 <_ZSt8_DestroyIPSsEvT_S1_>:
    3222:	55                   	push   %rbp
    3223:	48 89 e5             	mov    %rsp,%rbp
    3226:	48 83 ec 20          	sub    $0x20,%rsp
    322a:	48 89 7d f8          	mov    %rdi,0xfffffffffffffff8(%rbp)
    322e:	48 89 75 f0          	mov    %rsi,0xfffffffffffffff0(%rbp)
    3232:	48 8b 75 f0          	mov    0xfffffffffffffff0(%rbp),%rsi
    3236:	48 8b 7d f8          	mov    0xfffffffffffffff8(%rbp),%rdi
    323a:	0f b6 45 ef          	movzbl 0xffffffffffffffef(%rbp),%eax
    323e:	88 04 24             	mov    %al,(%rsp)
    3241:	e8 6a f3 ff ff       	callq  25b0 <_ZSt13__destroy_auxIPSsEvT_S1_12__false_type@plt>
    3246:	c9                   	leaveq 
    3247:	c3                   	retq   

0000000000003248 <_ZSt8_DestroyIPSsSsEvT_S1_SaIT0_E>:
    3248:	55                   	push   %rbp
    3249:	48 89 e5             	mov    %rsp,%rbp
    324c:	48 83 ec 20          	sub    $0x20,%rsp
    3250:	48 89 7d f8          	mov    %rdi,0xfffffffffffffff8(%rbp)
    3254:	48 89 75 f0          	mov    %rsi,0xfffffffffffffff0(%rbp)
    3258:	48 89 55 e8          	mov    %rdx,0xffffffffffffffe8(%rbp)
    325c:	48 8b 75 f0          	mov    0xfffffffffffffff0(%rbp),%rsi
    3260:	48 8b 7d f8          	mov    0xfffffffffffffff8(%rbp),%rdi
    3264:	e8 d7 f6 ff ff       	callq  2940 <_ZSt8_DestroyIPSsEvT_S1_@plt>
    3269:	c9                   	leaveq 
    326a:	c3                   	retq   
    326b:	90                   	nop    

000000000000326c <_ZNK9__gnu_cxx13new_allocatorISsE8max_sizeEv>:
    326c:	55                   	push   %rbp
    326d:	48 89 e5             	mov    %rsp,%rbp
    3270:	48 89 7d f8          	mov    %rdi,0xfffffffffffffff8(%rbp)
    3274:	48 b8 ff ff ff ff ff 	mov    $0x1fffffffffffffff,%rax
    327b:	ff ff 1f 
    327e:	c9                   	leaveq 
    327f:	c3                   	retq   

0000000000003280 <_ZNSt15__copy_backwardILb0ESt26random_access_iterator_tagE6copy_bIPSsS3_EET0_T_S5_S4_>:
    3280:	55                   	push   %rbp
    3281:	48 89 e5             	mov    %rsp,%rbp
    3284:	48 83 ec 30          	sub    $0x30,%rsp
    3288:	48 89 7d e8          	mov    %rdi,0xffffffffffffffe8(%rbp)
    328c:	48 89 75 e0          	mov    %rsi,0xffffffffffffffe0(%rbp)
    3290:	48 89 55 d8          	mov    %rdx,0xffffffffffffffd8(%rbp)
    3294:	48 8b 55 e0          	mov    0xffffffffffffffe0(%rbp),%rdx
    3298:	48 8b 45 e8          	mov    0xffffffffffffffe8(%rbp),%rax
    329c:	48 89 d1             	mov    %rdx,%rcx
    329f:	48 29 c1             	sub    %rax,%rcx
    32a2:	48 89 c8             	mov    %rcx,%rax
    32a5:	48 c1 f8 03          	sar    $0x3,%rax
    32a9:	48 89 45 f8          	mov    %rax,0xfffffffffffffff8(%rbp)
    32ad:	eb 1c                	jmp    32cb <_ZNSt15__copy_backwardILb0ESt26random_access_iterator_tagE6copy_bIPSsS3_EET0_T_S5_S4_+0x4b>
    32af:	48 83 6d e0 08       	subq   $0x8,0xffffffffffffffe0(%rbp)
    32b4:	48 83 6d d8 08       	subq   $0x8,0xffffffffffffffd8(%rbp)
    32b9:	48 8b 75 e0          	mov    0xffffffffffffffe0(%rbp),%rsi
    32bd:	48 8b 7d d8          	mov    0xffffffffffffffd8(%rbp),%rdi
    32c1:	e8 4a f6 ff ff       	callq  2910 <_ZNSsaSERKSs@plt>
    32c6:	48 83 6d f8 01       	subq   $0x1,0xfffffffffffffff8(%rbp)
    32cb:	48 83 7d f8 00       	cmpq   $0x0,0xfffffffffffffff8(%rbp)
    32d0:	7f dd                	jg     32af <_ZNSt15__copy_backwardILb0ESt26random_access_iterator_tagE6copy_bIPSsS3_EET0_T_S5_S4_+0x2f>
    32d2:	48 8b 45 d8          	mov    0xffffffffffffffd8(%rbp),%rax
    32d6:	c9                   	leaveq 
    32d7:	c3                   	retq   

00000000000032d8 <_ZSt19__copy_backward_auxIPSsS0_ET0_T_S2_S1_>:
    32d8:	55                   	push   %rbp
    32d9:	48 89 e5             	mov    %rsp,%rbp
    32dc:	48 83 ec 30          	sub    $0x30,%rsp
    32e0:	48 89 7d e8          	mov    %rdi,0xffffffffffffffe8(%rbp)
    32e4:	48 89 75 e0          	mov    %rsi,0xffffffffffffffe0(%rbp)
    32e8:	48 89 55 d8          	mov    %rdx,0xffffffffffffffd8(%rbp)
    32ec:	c6 45 ff 00          	movb   $0x0,0xffffffffffffffff(%rbp)
    32f0:	48 8b 55 d8          	mov    0xffffffffffffffd8(%rbp),%rdx
    32f4:	48 8b 75 e0          	mov    0xffffffffffffffe0(%rbp),%rsi
    32f8:	48 8b 7d e8          	mov    0xffffffffffffffe8(%rbp),%rdi
    32fc:	e8 2f f2 ff ff       	callq  2530 <_ZNSt15__copy_backwardILb0ESt26random_access_iterator_tagE6copy_bIPSsS3_EET0_T_S5_S4_@plt>
    3301:	c9                   	leaveq 
    3302:	c3                   	retq   
    3303:	90                   	nop    

0000000000003304 <_ZNSt22__copy_backward_normalILb1ELb1EE8copy_b_nIN9__gnu_cxx17__normal_iteratorIPSsSt6vectorISsSaISsEEEES8_EET0_T_SA_S9_>:
    3304:	55                   	push   %rbp
    3305:	48 89 e5             	mov    %rsp,%rbp
    3308:	41 54                	push   %r12
    330a:	53                   	push   %rbx
    330b:	48 83 ec 30          	sub    $0x30,%rsp
    330f:	48 89 7d d8          	mov    %rdi,0xffffffffffffffd8(%rbp)
    3313:	48 89 75 d0          	mov    %rsi,0xffffffffffffffd0(%rbp)
    3317:	48 89 55 c8          	mov    %rdx,0xffffffffffffffc8(%rbp)
    331b:	48 8d 7d c8          	lea    0xffffffffffffffc8(%rbp),%rdi
    331f:	e8 3c f2 ff ff       	callq  2560 <_ZNK9__gnu_cxx17__normal_iteratorIPSsSt6vectorISsSaISsEEE4baseEv@plt>
    3324:	4c 8b 20             	mov    (%rax),%r12
    3327:	48 8d 7d d0          	lea    0xffffffffffffffd0(%rbp),%rdi
    332b:	e8 30 f2 ff ff       	callq  2560 <_ZNK9__gnu_cxx17__normal_iteratorIPSsSt6vectorISsSaISsEEE4baseEv@plt>
    3330:	48 8b 18             	mov    (%rax),%rbx
    3333:	48 8d 7d d8          	lea    0xffffffffffffffd8(%rbp),%rdi
    3337:	e8 24 f2 ff ff       	callq  2560 <_ZNK9__gnu_cxx17__normal_iteratorIPSsSt6vectorISsSaISsEEE4baseEv@plt>
    333c:	48 8b 38             	mov    (%rax),%rdi
    333f:	4c 89 e2             	mov    %r12,%rdx
    3342:	48 89 de             	mov    %rbx,%rsi
    3345:	e8 96 f4 ff ff       	callq  27e0 <_ZSt19__copy_backward_auxIPSsS0_ET0_T_S2_S1_@plt>
    334a:	48 89 45 e8          	mov    %rax,0xffffffffffffffe8(%rbp)
    334e:	48 8d 75 e8          	lea    0xffffffffffffffe8(%rbp),%rsi
    3352:	48 8d 7d e0          	lea    0xffffffffffffffe0(%rbp),%rdi
    3356:	e8 25 f4 ff ff       	callq  2780 <_ZN9__gnu_cxx17__normal_iteratorIPSsSt6vectorISsSaISsEEEC1ERKS1_@plt>
    335b:	48 8b 45 e0          	mov    0xffffffffffffffe0(%rbp),%rax
    335f:	48 83 c4 30          	add    $0x30,%rsp
    3363:	5b                   	pop    %rbx
    3364:	41 5c                	pop    %r12
    3366:	c9                   	leaveq 
    3367:	c3                   	retq   

0000000000003368 <_ZSt13copy_backwardIN9__gnu_cxx17__normal_iteratorIPSsSt6vectorISsSaISsEEEES6_ET0_T_S8_S7_>:
    3368:	55                   	push   %rbp
    3369:	48 89 e5             	mov    %rsp,%rbp
    336c:	48 83 ec 30          	sub    $0x30,%rsp
    3370:	48 89 7d e8          	mov    %rdi,0xffffffffffffffe8(%rbp)
    3374:	48 89 75 e0          	mov    %rsi,0xffffffffffffffe0(%rbp)
    3378:	48 89 55 d8          	mov    %rdx,0xffffffffffffffd8(%rbp)
    337c:	c6 45 fe 01          	movb   $0x1,0xfffffffffffffffe(%rbp)
    3380:	c6 45 ff 01          	movb   $0x1,0xffffffffffffffff(%rbp)
    3384:	48 8b 55 d8          	mov    0xffffffffffffffd8(%rbp),%rdx
    3388:	48 8b 75 e0          	mov    0xffffffffffffffe0(%rbp),%rsi
    338c:	48 8b 7d e8          	mov    0xffffffffffffffe8(%rbp),%rdi
    3390:	e8 bb f5 ff ff       	callq  2950 <_ZNSt22__copy_backward_normalILb1ELb1EE8copy_b_nIN9__gnu_cxx17__normal_iteratorIPSsSt6vectorISsSaISsEEEES8_EET0_T_SA_S9_@plt>
    3395:	c9                   	leaveq 
    3396:	c3                   	retq   
    3397:	90                   	nop    

0000000000003398 <_ZN9__gnu_cxxneIPSsSt6vectorISsSaISsEEEEbRKNS_17__normal_iteratorIT_T0_EESA_>:
    3398:	55                   	push   %rbp
    3399:	48 89 e5             	mov    %rsp,%rbp
    339c:	53                   	push   %rbx
    339d:	48 83 ec 18          	sub    $0x18,%rsp
    33a1:	48 89 7d f0          	mov    %rdi,0xfffffffffffffff0(%rbp)
    33a5:	48 89 75 e8          	mov    %rsi,0xffffffffffffffe8(%rbp)
    33a9:	48 8b 7d f0          	mov    0xfffffffffffffff0(%rbp),%rdi
    33ad:	e8 ae f1 ff ff       	callq  2560 <_ZNK9__gnu_cxx17__normal_iteratorIPSsSt6vectorISsSaISsEEE4baseEv@plt>
    33b2:	48 8b 18             	mov    (%rax),%rbx
    33b5:	48 8b 7d e8          	mov    0xffffffffffffffe8(%rbp),%rdi
    33b9:	e8 a2 f1 ff ff       	callq  2560 <_ZNK9__gnu_cxx17__normal_iteratorIPSsSt6vectorISsSaISsEEE4baseEv@plt>
    33be:	48 8b 00             	mov    (%rax),%rax
    33c1:	48 39 c3             	cmp    %rax,%rbx
    33c4:	0f 95 c0             	setne  %al
    33c7:	0f b6 c0             	movzbl %al,%eax
    33ca:	48 83 c4 18          	add    $0x18,%rsp
    33ce:	5b                   	pop    %rbx
    33cf:	c9                   	leaveq 
    33d0:	c3                   	retq   
    33d1:	90                   	nop    

00000000000033d2 <_ZSt13__destroy_auxIN9__gnu_cxx17__normal_iteratorIPSsSt6vectorISsSaISsEEEEEvT_S7_12__false_type>:
    33d2:	55                   	push   %rbp
    33d3:	48 89 e5             	mov    %rsp,%rbp
    33d6:	48 83 ec 10          	sub    $0x10,%rsp
    33da:	48 89 7d f8          	mov    %rdi,0xfffffffffffffff8(%rbp)
    33de:	48 89 75 f0          	mov    %rsi,0xfffffffffffffff0(%rbp)
    33e2:	eb 1a                	jmp    33fe <_ZSt13__destroy_auxIN9__gnu_cxx17__normal_iteratorIPSsSt6vectorISsSaISsEEEEEvT_S7_12__false_type+0x2c>
    33e4:	48 8d 7d f8          	lea    0xfffffffffffffff8(%rbp),%rdi
    33e8:	e8 43 f3 ff ff       	callq  2730 <_ZNK9__gnu_cxx17__normal_iteratorIPSsSt6vectorISsSaISsEEEdeEv@plt>
    33ed:	48 89 c7             	mov    %rax,%rdi
    33f0:	e8 4b f1 ff ff       	callq  2540 <_ZSt8_DestroyISsEvPT_@plt>
    33f5:	48 8d 7d f8          	lea    0xfffffffffffffff8(%rbp),%rdi
    33f9:	e8 62 f3 ff ff       	callq  2760 <_ZN9__gnu_cxx17__normal_iteratorIPSsSt6vectorISsSaISsEEEppEv@plt>
    33fe:	48 8d 75 f0          	lea    0xfffffffffffffff0(%rbp),%rsi
    3402:	48 8d 7d f8          	lea    0xfffffffffffffff8(%rbp),%rdi
    3406:	e8 35 f2 ff ff       	callq  2640 <_ZN9__gnu_cxxneIPSsSt6vectorISsSaISsEEEEbRKNS_17__normal_iteratorIT_T0_EESA_@plt>
    340b:	84 c0                	test   %al,%al
    340d:	75 d5                	jne    33e4 <_ZSt13__destroy_auxIN9__gnu_cxx17__normal_iteratorIPSsSt6vectorISsSaISsEEEEEvT_S7_12__false_type+0x12>
    340f:	c9                   	leaveq 
    3410:	c3                   	retq   
    3411:	90                   	nop    

0000000000003412 <_ZSt8_DestroyIN9__gnu_cxx17__normal_iteratorIPSsSt6vectorISsSaISsEEEEEvT_S7_>:
    3412:	55                   	push   %rbp
    3413:	48 89 e5             	mov    %rsp,%rbp
    3416:	48 83 ec 20          	sub    $0x20,%rsp
    341a:	48 89 7d f8          	mov    %rdi,0xfffffffffffffff8(%rbp)
    341e:	48 89 75 f0          	mov    %rsi,0xfffffffffffffff0(%rbp)
    3422:	48 8b 75 f0          	mov    0xfffffffffffffff0(%rbp),%rsi
    3426:	48 8b 7d f8          	mov    0xfffffffffffffff8(%rbp),%rdi
    342a:	0f b6 45 ef          	movzbl 0xffffffffffffffef(%rbp),%eax
    342e:	88 04 24             	mov    %al,(%rsp)
    3431:	e8 2a f4 ff ff       	callq  2860 <_ZSt13__destroy_auxIN9__gnu_cxx17__normal_iteratorIPSsSt6vectorISsSaISsEEEEEvT_S7_12__false_type@plt>
    3436:	c9                   	leaveq 
    3437:	c3                   	retq   

0000000000003438 <_ZSt8_DestroyIN9__gnu_cxx17__normal_iteratorIPSsSt6vectorISsSaISsEEEESsEvT_S7_SaIT0_E>:
    3438:	55                   	push   %rbp
    3439:	48 89 e5             	mov    %rsp,%rbp
    343c:	48 83 ec 20          	sub    $0x20,%rsp
    3440:	48 89 7d f8          	mov    %rdi,0xfffffffffffffff8(%rbp)
    3444:	48 89 75 f0          	mov    %rsi,0xfffffffffffffff0(%rbp)
    3448:	48 89 55 e8          	mov    %rdx,0xffffffffffffffe8(%rbp)
    344c:	48 8b 75 f0          	mov    0xfffffffffffffff0(%rbp),%rsi
    3450:	48 8b 7d f8          	mov    0xfffffffffffffff8(%rbp),%rdi
    3454:	e8 27 f0 ff ff       	callq  2480 <_ZSt8_DestroyIN9__gnu_cxx17__normal_iteratorIPSsSt6vectorISsSaISsEEEEEvT_S7_@plt>
    3459:	c9                   	leaveq 
    345a:	c3                   	retq   
    345b:	90                   	nop    

000000000000345c <_ZN9__gnu_cxx13new_allocatorISsE10deallocateEPSsm>:
    345c:	55                   	push   %rbp
    345d:	48 89 e5             	mov    %rsp,%rbp
    3460:	48 83 ec 20          	sub    $0x20,%rsp
    3464:	48 89 7d f8          	mov    %rdi,0xfffffffffffffff8(%rbp)
    3468:	48 89 75 f0          	mov    %rsi,0xfffffffffffffff0(%rbp)
    346c:	48 89 55 e8          	mov    %rdx,0xffffffffffffffe8(%rbp)
    3470:	48 8b 7d f0          	mov    0xfffffffffffffff0(%rbp),%rdi
    3474:	e8 67 f0 ff ff       	callq  24e0 <_ZdlPv@plt>
    3479:	c9                   	leaveq 
    347a:	c3                   	retq   
    347b:	90                   	nop    

000000000000347c <_ZNSt12_Vector_baseISsSaISsEE13_M_deallocateEPSsm>:
    347c:	55                   	push   %rbp
    347d:	48 89 e5             	mov    %rsp,%rbp
    3480:	48 83 ec 20          	sub    $0x20,%rsp
    3484:	48 89 7d f8          	mov    %rdi,0xfffffffffffffff8(%rbp)
    3488:	48 89 75 f0          	mov    %rsi,0xfffffffffffffff0(%rbp)
    348c:	48 89 55 e8          	mov    %rdx,0xffffffffffffffe8(%rbp)
    3490:	48 83 7d f0 00       	cmpq   $0x0,0xfffffffffffffff0(%rbp)
    3495:	74 14                	je     34ab <_ZNSt12_Vector_baseISsSaISsEE13_M_deallocateEPSsm+0x2f>
    3497:	48 8b 45 f8          	mov    0xfffffffffffffff8(%rbp),%rax
    349b:	48 89 c7             	mov    %rax,%rdi
    349e:	48 8b 55 e8          	mov    0xffffffffffffffe8(%rbp),%rdx
    34a2:	48 8b 75 f0          	mov    0xfffffffffffffff0(%rbp),%rsi
    34a6:	e8 35 f2 ff ff       	callq  26e0 <_ZN9__gnu_cxx13new_allocatorISsE10deallocateEPSsm@plt>
    34ab:	c9                   	leaveq 
    34ac:	c3                   	retq   
    34ad:	90                   	nop    

00000000000034ae <_ZNSt12_Vector_baseISsSaISsEED2Ev>:
    34ae:	55                   	push   %rbp
    34af:	48 89 e5             	mov    %rsp,%rbp
    34b2:	48 83 ec 10          	sub    $0x10,%rsp
    34b6:	48 89 7d f8          	mov    %rdi,0xfffffffffffffff8(%rbp)
    34ba:	48 8b 45 f8          	mov    0xfffffffffffffff8(%rbp),%rax
    34be:	48 8b 40 10          	mov    0x10(%rax),%rax
    34c2:	48 89 c2             	mov    %rax,%rdx
    34c5:	48 8b 45 f8          	mov    0xfffffffffffffff8(%rbp),%rax
    34c9:	48 8b 00             	mov    (%rax),%rax
    34cc:	48 89 d1             	mov    %rdx,%rcx
    34cf:	48 29 c1             	sub    %rax,%rcx
    34d2:	48 89 c8             	mov    %rcx,%rax
    34d5:	48 c1 f8 03          	sar    $0x3,%rax
    34d9:	48 89 c2             	mov    %rax,%rdx
    34dc:	48 8b 45 f8          	mov    0xfffffffffffffff8(%rbp),%rax
    34e0:	48 8b 30             	mov    (%rax),%rsi
    34e3:	48 8b 7d f8          	mov    0xfffffffffffffff8(%rbp),%rdi
    34e7:	e8 b4 f0 ff ff       	callq  25a0 <_ZNSt12_Vector_baseISsSaISsEE13_M_deallocateEPSsm@plt>
    34ec:	48 8b 7d f8          	mov    0xfffffffffffffff8(%rbp),%rdi
    34f0:	e8 5b ef ff ff       	callq  2450 <_ZNSt12_Vector_baseISsSaISsEE12_Vector_implD1Ev@plt>
    34f5:	c9                   	leaveq 
    34f6:	c3                   	retq   
    34f7:	90                   	nop    

00000000000034f8 <_ZNSt6vectorISsSaISsEED1Ev>:
    34f8:	55                   	push   %rbp
    34f9:	48 89 e5             	mov    %rsp,%rbp
    34fc:	53                   	push   %rbx
    34fd:	48 83 ec 28          	sub    $0x28,%rsp
    3501:	48 89 7d e0          	mov    %rdi,0xffffffffffffffe0(%rbp)
    3505:	48 8b 7d e0          	mov    0xffffffffffffffe0(%rbp),%rdi
    3509:	e8 12 f0 ff ff       	callq  2520 <_ZNSt12_Vector_baseISsSaISsEE19_M_get_Tp_allocatorEv@plt>
    350e:	48 89 c6             	mov    %rax,%rsi
    3511:	48 8d 7d f7          	lea    0xfffffffffffffff7(%rbp),%rdi
    3515:	e8 36 f0 ff ff       	callq  2550 <_ZNSaISsEC1ERKS_@plt>
    351a:	48 8b 45 e0          	mov    0xffffffffffffffe0(%rbp),%rax
    351e:	48 8b 70 08          	mov    0x8(%rax),%rsi
    3522:	48 8b 45 e0          	mov    0xffffffffffffffe0(%rbp),%rax
    3526:	48 8b 38             	mov    (%rax),%rdi
    3529:	48 8d 55 f7          	lea    0xfffffffffffffff7(%rbp),%rdx
    352d:	e8 3e f1 ff ff       	callq  2670 <_ZSt8_DestroyIPSsSsEvT_S1_SaIT0_E@plt>
    3532:	48 8d 7d f7          	lea    0xfffffffffffffff7(%rbp),%rdi
    3536:	e8 65 ef ff ff       	callq  24a0 <_ZNSaISsED1Ev@plt>
    353b:	48 8b 45 e0          	mov    0xffffffffffffffe0(%rbp),%rax
    353f:	48 89 45 d8          	mov    %rax,0xffffffffffffffd8(%rbp)
    3543:	48 8b 7d d8          	mov    0xffffffffffffffd8(%rbp),%rdi
    3547:	e8 f4 ee ff ff       	callq  2440 <_ZNSt12_Vector_baseISsSaISsEED2Ev@plt>
    354c:	eb 37                	jmp    3585 <_ZNSt6vectorISsSaISsEED1Ev+0x8d>
    354e:	48 89 45 d0          	mov    %rax,0xffffffffffffffd0(%rbp)
    3552:	48 8b 5d d0          	mov    0xffffffffffffffd0(%rbp),%rbx
    3556:	48 8d 7d f7          	lea    0xfffffffffffffff7(%rbp),%rdi
    355a:	e8 41 ef ff ff       	callq  24a0 <_ZNSaISsED1Ev@plt>
    355f:	48 89 5d d0          	mov    %rbx,0xffffffffffffffd0(%rbp)
    3563:	48 8b 5d d0          	mov    0xffffffffffffffd0(%rbp),%rbx
    3567:	48 8b 45 e0          	mov    0xffffffffffffffe0(%rbp),%rax
    356b:	48 89 45 d8          	mov    %rax,0xffffffffffffffd8(%rbp)
    356f:	48 8b 7d d8          	mov    0xffffffffffffffd8(%rbp),%rdi
    3573:	e8 c8 ee ff ff       	callq  2440 <_ZNSt12_Vector_baseISsSaISsEED2Ev@plt>
    3578:	48 89 5d d0          	mov    %rbx,0xffffffffffffffd0(%rbp)
    357c:	48 8b 7d d0          	mov    0xffffffffffffffd0(%rbp),%rdi
    3580:	e8 3b f3 ff ff       	callq  28c0 <_Unwind_Resume@plt>
    3585:	48 83 c4 28          	add    $0x28,%rsp
    3589:	5b                   	pop    %rbx
    358a:	c9                   	leaveq 
    358b:	c3                   	retq   

000000000000358c <_ZN4TestC1ERKSs>:
    358c:	55                   	push   %rbp
    358d:	48 89 e5             	mov    %rsp,%rbp
    3590:	53                   	push   %rbx
    3591:	48 83 ec 28          	sub    $0x28,%rsp
    3595:	48 89 7d e0          	mov    %rdi,0xffffffffffffffe0(%rbp)
    3599:	48 89 75 d8          	mov    %rsi,0xffffffffffffffd8(%rbp)
    359d:	48 8d 7d f7          	lea    0xfffffffffffffff7(%rbp),%rdi
    35a1:	e8 8a f3 ff ff       	callq  2930 <_ZNSaISsEC1Ev@plt>
    35a6:	48 8b 7d e0          	mov    0xffffffffffffffe0(%rbp),%rdi
    35aa:	48 8d 75 f7          	lea    0xfffffffffffffff7(%rbp),%rsi
    35ae:	e8 6d f2 ff ff       	callq  2820 <_ZNSt6vectorISsSaISsEEC1ERKS0_@plt>
    35b3:	48 8d 7d f7          	lea    0xfffffffffffffff7(%rbp),%rdi
    35b7:	e8 e4 ee ff ff       	callq  24a0 <_ZNSaISsED1Ev@plt>
    35bc:	48 8d 35 c8 08 00 00 	lea    2248(%rip),%rsi        # 3e8b <_fini+0x23>
    35c3:	48 8b 3d 3e 1c 20 00 	mov    2104382(%rip),%rdi        # 205208 <_DYNAMIC+0x1c8>
    35ca:	e8 21 f0 ff ff       	callq  25f0 <_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@plt>
    35cf:	48 89 c7             	mov    %rax,%rdi
    35d2:	48 8b 75 d8          	mov    0xffffffffffffffd8(%rbp),%rsi
    35d6:	e8 c5 f1 ff ff       	callq  27a0 <_ZStlsIcSt11char_traitsIcESaIcEERSt13basic_ostreamIT_T0_ES7_RKSbIS4_S5_T1_E@plt>
    35db:	48 89 c7             	mov    %rax,%rdi
    35de:	48 8b 35 3b 1c 20 00 	mov    2104379(%rip),%rsi        # 205220 <_DYNAMIC+0x1e0>
    35e5:	e8 26 f2 ff ff       	callq  2810 <_ZNSolsEPFRSoS_E@plt>
    35ea:	eb 1e                	jmp    360a <_ZN4TestC1ERKSs+0x7e>
    35ec:	48 89 45 d0          	mov    %rax,0xffffffffffffffd0(%rbp)
    35f0:	48 8b 5d d0          	mov    0xffffffffffffffd0(%rbp),%rbx
    35f4:	48 8b 7d e0          	mov    0xffffffffffffffe0(%rbp),%rdi
    35f8:	e8 83 f2 ff ff       	callq  2880 <_ZNSt6vectorISsSaISsEED1Ev@plt>
    35fd:	48 89 5d d0          	mov    %rbx,0xffffffffffffffd0(%rbp)
    3601:	48 8b 7d d0          	mov    0xffffffffffffffd0(%rbp),%rdi
    3605:	e8 b6 f2 ff ff       	callq  28c0 <_Unwind_Resume@plt>
    360a:	48 83 c4 28          	add    $0x28,%rsp
    360e:	5b                   	pop    %rbx
    360f:	c9                   	leaveq 
    3610:	c3                   	retq   
    3611:	90                   	nop    

0000000000003612 <_ZN4TestD1Ev>:
    3612:	55                   	push   %rbp
    3613:	48 89 e5             	mov    %rsp,%rbp
    3616:	53                   	push   %rbx
    3617:	48 83 ec 18          	sub    $0x18,%rsp
    361b:	48 89 7d f0          	mov    %rdi,0xfffffffffffffff0(%rbp)
    361f:	48 8d 35 75 08 00 00 	lea    2165(%rip),%rsi        # 3e9b <_fini+0x33>
    3626:	48 8b 3d db 1b 20 00 	mov    2104283(%rip),%rdi        # 205208 <_DYNAMIC+0x1c8>
    362d:	e8 be ef ff ff       	callq  25f0 <_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@plt>
    3632:	48 89 c7             	mov    %rax,%rdi
    3635:	48 8b 35 e4 1b 20 00 	mov    2104292(%rip),%rsi        # 205220 <_DYNAMIC+0x1e0>
    363c:	e8 cf f1 ff ff       	callq  2810 <_ZNSolsEPFRSoS_E@plt>
    3641:	48 8b 45 f0          	mov    0xfffffffffffffff0(%rbp),%rax
    3645:	48 89 45 e8          	mov    %rax,0xffffffffffffffe8(%rbp)
    3649:	48 8b 7d e8          	mov    0xffffffffffffffe8(%rbp),%rdi
    364d:	e8 2e f2 ff ff       	callq  2880 <_ZNSt6vectorISsSaISsEED1Ev@plt>
    3652:	eb 26                	jmp    367a <_ZN4TestD1Ev+0x68>
    3654:	48 89 45 e0          	mov    %rax,0xffffffffffffffe0(%rbp)
    3658:	48 8b 5d e0          	mov    0xffffffffffffffe0(%rbp),%rbx
    365c:	48 8b 45 f0          	mov    0xfffffffffffffff0(%rbp),%rax
    3660:	48 89 45 e8          	mov    %rax,0xffffffffffffffe8(%rbp)
    3664:	48 8b 7d e8          	mov    0xffffffffffffffe8(%rbp),%rdi
    3668:	e8 13 f2 ff ff       	callq  2880 <_ZNSt6vectorISsSaISsEED1Ev@plt>
    366d:	48 89 5d e0          	mov    %rbx,0xffffffffffffffe0(%rbp)
    3671:	48 8b 7d e0          	mov    0xffffffffffffffe0(%rbp),%rdi
    3675:	e8 46 f2 ff ff       	callq  28c0 <_Unwind_Resume@plt>
    367a:	48 83 c4 18          	add    $0x18,%rsp
    367e:	5b                   	pop    %rbx
    367f:	c9                   	leaveq 
    3680:	c3                   	retq   
    3681:	90                   	nop    

0000000000003682 <_ZN9__gnu_cxx13new_allocatorISsE9constructEPSsRKSs>:
    3682:	55                   	push   %rbp
    3683:	48 89 e5             	mov    %rsp,%rbp
    3686:	53                   	push   %rbx
    3687:	48 83 ec 28          	sub    $0x28,%rsp
    368b:	48 89 7d f0          	mov    %rdi,0xfffffffffffffff0(%rbp)
    368f:	48 89 75 e8          	mov    %rsi,0xffffffffffffffe8(%rbp)
    3693:	48 89 55 e0          	mov    %rdx,0xffffffffffffffe0(%rbp)
    3697:	48 8b 75 e8          	mov    0xffffffffffffffe8(%rbp),%rsi
    369b:	bf 08 00 00 00       	mov    $0x8,%edi
    36a0:	e8 eb ee ff ff       	callq  2590 <_ZnwmPv@plt>
    36a5:	48 89 45 d8          	mov    %rax,0xffffffffffffffd8(%rbp)
    36a9:	48 83 7d d8 00       	cmpq   $0x0,0xffffffffffffffd8(%rbp)
    36ae:	74 31                	je     36e1 <_ZN9__gnu_cxx13new_allocatorISsE9constructEPSsRKSs+0x5f>
    36b0:	48 8b 75 e0          	mov    0xffffffffffffffe0(%rbp),%rsi
    36b4:	48 8b 7d d8          	mov    0xffffffffffffffd8(%rbp),%rdi
    36b8:	e8 b3 ee ff ff       	callq  2570 <_ZNSsC1ERKSs@plt>
    36bd:	eb 22                	jmp    36e1 <_ZN9__gnu_cxx13new_allocatorISsE9constructEPSsRKSs+0x5f>
    36bf:	48 89 45 d0          	mov    %rax,0xffffffffffffffd0(%rbp)
    36c3:	48 8b 5d d0          	mov    0xffffffffffffffd0(%rbp),%rbx
    36c7:	48 8b 75 e8          	mov    0xffffffffffffffe8(%rbp),%rsi
    36cb:	48 8b 7d d8          	mov    0xffffffffffffffd8(%rbp),%rdi
    36cf:	e8 cc f1 ff ff       	callq  28a0 <_ZdlPvS_@plt>
    36d4:	48 89 5d d0          	mov    %rbx,0xffffffffffffffd0(%rbp)
    36d8:	48 8b 7d d0          	mov    0xffffffffffffffd0(%rbp),%rdi
    36dc:	e8 df f1 ff ff       	callq  28c0 <_Unwind_Resume@plt>
    36e1:	48 83 c4 28          	add    $0x28,%rsp
    36e5:	5b                   	pop    %rbx
    36e6:	c9                   	leaveq 
    36e7:	c3                   	retq   

00000000000036e8 <_ZSt10_ConstructISsSsEvPT_RKT0_>:
    36e8:	55                   	push   %rbp
    36e9:	48 89 e5             	mov    %rsp,%rbp
    36ec:	53                   	push   %rbx
    36ed:	48 83 ec 28          	sub    $0x28,%rsp
    36f1:	48 89 7d f0          	mov    %rdi,0xfffffffffffffff0(%rbp)
    36f5:	48 89 75 e8          	mov    %rsi,0xffffffffffffffe8(%rbp)
    36f9:	48 8b 75 f0          	mov    0xfffffffffffffff0(%rbp),%rsi
    36fd:	bf 08 00 00 00       	mov    $0x8,%edi
    3702:	e8 89 ee ff ff       	callq  2590 <_ZnwmPv@plt>
    3707:	48 89 45 e0          	mov    %rax,0xffffffffffffffe0(%rbp)
    370b:	48 83 7d e0 00       	cmpq   $0x0,0xffffffffffffffe0(%rbp)
    3710:	74 31                	je     3743 <_ZSt10_ConstructISsSsEvPT_RKT0_+0x5b>
    3712:	48 8b 75 e8          	mov    0xffffffffffffffe8(%rbp),%rsi
    3716:	48 8b 7d e0          	mov    0xffffffffffffffe0(%rbp),%rdi
    371a:	e8 51 ee ff ff       	callq  2570 <_ZNSsC1ERKSs@plt>
    371f:	eb 22                	jmp    3743 <_ZSt10_ConstructISsSsEvPT_RKT0_+0x5b>
    3721:	48 89 45 d8          	mov    %rax,0xffffffffffffffd8(%rbp)
    3725:	48 8b 5d d8          	mov    0xffffffffffffffd8(%rbp),%rbx
    3729:	48 8b 75 f0          	mov    0xfffffffffffffff0(%rbp),%rsi
    372d:	48 8b 7d e0          	mov    0xffffffffffffffe0(%rbp),%rdi
    3731:	e8 6a f1 ff ff       	callq  28a0 <_ZdlPvS_@plt>
    3736:	48 89 5d d8          	mov    %rbx,0xffffffffffffffd8(%rbp)
    373a:	48 8b 7d d8          	mov    0xffffffffffffffd8(%rbp),%rdi
    373e:	e8 7d f1 ff ff       	callq  28c0 <_Unwind_Resume@plt>
    3743:	48 83 c4 28          	add    $0x28,%rsp
    3747:	5b                   	pop    %rbx
    3748:	c9                   	leaveq 
    3749:	c3                   	retq   

000000000000374a <_ZSt24__uninitialized_copy_auxIN9__gnu_cxx17__normal_iteratorIPSsSt6vectorISsSaISsEEEES6_ET0_T_S8_S7_12__false_type>:
    374a:	55                   	push   %rbp
    374b:	48 89 e5             	mov    %rsp,%rbp
    374e:	53                   	push   %rbx
    374f:	48 83 ec 48          	sub    $0x48,%rsp
    3753:	48 89 7d d8          	mov    %rdi,0xffffffffffffffd8(%rbp)
    3757:	48 89 75 d0          	mov    %rsi,0xffffffffffffffd0(%rbp)
    375b:	48 89 55 c8          	mov    %rdx,0xffffffffffffffc8(%rbp)
    375f:	48 8b 45 c8          	mov    0xffffffffffffffc8(%rbp),%rax
    3763:	48 89 45 e0          	mov    %rax,0xffffffffffffffe0(%rbp)
    3767:	eb 32                	jmp    379b <_ZSt24__uninitialized_copy_auxIN9__gnu_cxx17__normal_iteratorIPSsSt6vectorISsSaISsEEEES6_ET0_T_S8_S7_12__false_type+0x51>
    3769:	48 8d 7d d8          	lea    0xffffffffffffffd8(%rbp),%rdi
    376d:	e8 be ef ff ff       	callq  2730 <_ZNK9__gnu_cxx17__normal_iteratorIPSsSt6vectorISsSaISsEEEdeEv@plt>
    3772:	48 89 c3             	mov    %rax,%rbx
    3775:	48 8d 7d e0          	lea    0xffffffffffffffe0(%rbp),%rdi
    3779:	e8 b2 ef ff ff       	callq  2730 <_ZNK9__gnu_cxx17__normal_iteratorIPSsSt6vectorISsSaISsEEEdeEv@plt>
    377e:	48 89 c7             	mov    %rax,%rdi
    3781:	48 89 de             	mov    %rbx,%rsi
    3784:	e8 07 ed ff ff       	callq  2490 <_ZSt10_ConstructISsSsEvPT_RKT0_@plt>
    3789:	48 8d 7d d8          	lea    0xffffffffffffffd8(%rbp),%rdi
    378d:	e8 ce ef ff ff       	callq  2760 <_ZN9__gnu_cxx17__normal_iteratorIPSsSt6vectorISsSaISsEEEppEv@plt>
    3792:	48 8d 7d e0          	lea    0xffffffffffffffe0(%rbp),%rdi
    3796:	e8 c5 ef ff ff       	callq  2760 <_ZN9__gnu_cxx17__normal_iteratorIPSsSt6vectorISsSaISsEEEppEv@plt>
    379b:	48 8d 75 d0          	lea    0xffffffffffffffd0(%rbp),%rsi
    379f:	48 8d 7d d8          	lea    0xffffffffffffffd8(%rbp),%rdi
    37a3:	e8 98 ee ff ff       	callq  2640 <_ZN9__gnu_cxxneIPSsSt6vectorISsSaISsEEEEbRKNS_17__normal_iteratorIT_T0_EESA_@plt>
    37a8:	84 c0                	test   %al,%al
    37aa:	75 bd                	jne    3769 <_ZSt24__uninitialized_copy_auxIN9__gnu_cxx17__normal_iteratorIPSsSt6vectorISsSaISsEEEES6_ET0_T_S8_S7_12__false_type+0x1f>
    37ac:	48 8b 45 e0          	mov    0xffffffffffffffe0(%rbp),%rax
    37b0:	48 89 45 c0          	mov    %rax,0xffffffffffffffc0(%rbp)
    37b4:	eb 39                	jmp    37ef <_ZSt24__uninitialized_copy_auxIN9__gnu_cxx17__normal_iteratorIPSsSt6vectorISsSaISsEEEES6_ET0_T_S8_S7_12__false_type+0xa5>
    37b6:	48 89 45 b8          	mov    %rax,0xffffffffffffffb8(%rbp)
    37ba:	48 8b 7d b8          	mov    0xffffffffffffffb8(%rbp),%rdi
    37be:	e8 ad f0 ff ff       	callq  2870 <__cxa_begin_catch@plt>
    37c3:	48 8b 75 e0          	mov    0xffffffffffffffe0(%rbp),%rsi
    37c7:	48 8b 7d c8          	mov    0xffffffffffffffc8(%rbp),%rdi
    37cb:	e8 b0 ec ff ff       	callq  2480 <_ZSt8_DestroyIN9__gnu_cxx17__normal_iteratorIPSsSt6vectorISsSaISsEEEEEvT_S7_@plt>
    37d0:	e8 2b ed ff ff       	callq  2500 <__cxa_rethrow@plt>
    37d5:	48 89 45 b8          	mov    %rax,0xffffffffffffffb8(%rbp)
    37d9:	48 8b 5d b8          	mov    0xffffffffffffffb8(%rbp),%rbx
    37dd:	e8 4e f0 ff ff       	callq  2830 <__cxa_end_catch@plt>
    37e2:	48 89 5d b8          	mov    %rbx,0xffffffffffffffb8(%rbp)
    37e6:	48 8b 7d b8          	mov    0xffffffffffffffb8(%rbp),%rdi
    37ea:	e8 d1 f0 ff ff       	callq  28c0 <_Unwind_Resume@plt>
    37ef:	48 8b 45 c0          	mov    0xffffffffffffffc0(%rbp),%rax
    37f3:	48 83 c4 48          	add    $0x48,%rsp
    37f7:	5b                   	pop    %rbx
    37f8:	c9                   	leaveq 
    37f9:	c3                   	retq   

00000000000037fa <_ZSt18uninitialized_copyIN9__gnu_cxx17__normal_iteratorIPSsSt6vectorISsSaISsEEEES6_ET0_T_S8_S7_>:
    37fa:	55                   	push   %rbp
    37fb:	48 89 e5             	mov    %rsp,%rbp
    37fe:	48 83 ec 30          	sub    $0x30,%rsp
    3802:	48 89 7d f8          	mov    %rdi,0xfffffffffffffff8(%rbp)
    3806:	48 89 75 f0          	mov    %rsi,0xfffffffffffffff0(%rbp)
    380a:	48 89 55 e8          	mov    %rdx,0xffffffffffffffe8(%rbp)
    380e:	48 8b 55 e8          	mov    0xffffffffffffffe8(%rbp),%rdx
    3812:	48 8b 75 f0          	mov    0xfffffffffffffff0(%rbp),%rsi
    3816:	48 8b 7d f8          	mov    0xfffffffffffffff8(%rbp),%rdi
    381a:	0f b6 45 e7          	movzbl 0xffffffffffffffe7(%rbp),%eax
    381e:	88 04 24             	mov    %al,(%rsp)
    3821:	e8 da ef ff ff       	callq  2800 <_ZSt24__uninitialized_copy_auxIN9__gnu_cxx17__normal_iteratorIPSsSt6vectorISsSaISsEEEES6_ET0_T_S8_S7_12__false_type@plt>
    3826:	c9                   	leaveq 
    3827:	c3                   	retq   

0000000000003828 <_ZSt22__uninitialized_copy_aIN9__gnu_cxx17__normal_iteratorIPSsSt6vectorISsSaISsEEEES6_SsET0_T_S8_S7_SaIT1_E>:
    3828:	55                   	push   %rbp
    3829:	48 89 e5             	mov    %rsp,%rbp
    382c:	48 83 ec 20          	sub    $0x20,%rsp
    3830:	48 89 7d f8          	mov    %rdi,0xfffffffffffffff8(%rbp)
    3834:	48 89 75 f0          	mov    %rsi,0xfffffffffffffff0(%rbp)
    3838:	48 89 55 e8          	mov    %rdx,0xffffffffffffffe8(%rbp)
    383c:	48 89 4d e0          	mov    %rcx,0xffffffffffffffe0(%rbp)
    3840:	48 8b 55 e8          	mov    0xffffffffffffffe8(%rbp),%rdx
    3844:	48 8b 75 f0          	mov    0xfffffffffffffff0(%rbp),%rsi
    3848:	48 8b 7d f8          	mov    0xfffffffffffffff8(%rbp),%rdi
    384c:	e8 9f ef ff ff       	callq  27f0 <_ZSt18uninitialized_copyIN9__gnu_cxx17__normal_iteratorIPSsSt6vectorISsSaISsEEEES6_ET0_T_S8_S7_@plt>
    3851:	c9                   	leaveq 
    3852:	c3                   	retq   
    3853:	90                   	nop    

0000000000003854 <_ZN9__gnu_cxx13new_allocatorISsE8allocateEmPKv>:
    3854:	55                   	push   %rbp
    3855:	48 89 e5             	mov    %rsp,%rbp
    3858:	48 83 ec 20          	sub    $0x20,%rsp
    385c:	48 89 7d f8          	mov    %rdi,0xfffffffffffffff8(%rbp)
    3860:	48 89 75 f0          	mov    %rsi,0xfffffffffffffff0(%rbp)
    3864:	48 89 55 e8          	mov    %rdx,0xffffffffffffffe8(%rbp)
    3868:	48 8b 7d f8          	mov    0xfffffffffffffff8(%rbp),%rdi
    386c:	e8 3f ef ff ff       	callq  27b0 <_ZNK9__gnu_cxx13new_allocatorISsE8max_sizeEv@plt>
    3871:	48 3b 45 f0          	cmp    0xfffffffffffffff0(%rbp),%rax
    3875:	0f 92 c0             	setb   %al
    3878:	0f b6 c0             	movzbl %al,%eax
    387b:	48 85 c0             	test   %rax,%rax
    387e:	0f 95 c0             	setne  %al
    3881:	84 c0                	test   %al,%al
    3883:	74 05                	je     388a <_ZN9__gnu_cxx13new_allocatorISsE8allocateEmPKv+0x36>
    3885:	e8 b6 ef ff ff       	callq  2840 <_ZSt17__throw_bad_allocv@plt>
    388a:	48 8b 45 f0          	mov    0xfffffffffffffff0(%rbp),%rax
    388e:	48 8d 3c c5 00 00 00 	lea    0x0(,%rax,8),%rdi
    3895:	00 
    3896:	e8 15 f0 ff ff       	callq  28b0 <_Znwm@plt>
    389b:	c9                   	leaveq 
    389c:	c3                   	retq   
    389d:	90                   	nop    

000000000000389e <_ZNSt12_Vector_baseISsSaISsEE11_M_allocateEm>:
    389e:	55                   	push   %rbp
    389f:	48 89 e5             	mov    %rsp,%rbp
    38a2:	48 83 ec 10          	sub    $0x10,%rsp
    38a6:	48 89 7d f8          	mov    %rdi,0xfffffffffffffff8(%rbp)
    38aa:	48 89 75 f0          	mov    %rsi,0xfffffffffffffff0(%rbp)
    38ae:	48 8b 45 f8          	mov    0xfffffffffffffff8(%rbp),%rax
    38b2:	48 89 c7             	mov    %rax,%rdi
    38b5:	48 8b 75 f0          	mov    0xfffffffffffffff0(%rbp),%rsi
    38b9:	ba 00 00 00 00       	mov    $0x0,%edx
    38be:	e8 cd ed ff ff       	callq  2690 <_ZN9__gnu_cxx13new_allocatorISsE8allocateEmPKv@plt>
    38c3:	c9                   	leaveq 
    38c4:	c3                   	retq   
    38c5:	90                   	nop    

00000000000038c6 <_ZNSt6vectorISsSaISsEE13_M_insert_auxEN9__gnu_cxx17__normal_iteratorIPSsS1_EERKSs>:
    38c6:	55                   	push   %rbp
    38c7:	48 89 e5             	mov    %rsp,%rbp
    38ca:	53                   	push   %rbx
    38cb:	48 81 ec c8 00 00 00 	sub    $0xc8,%rsp
    38d2:	48 89 bd 58 ff ff ff 	mov    %rdi,0xffffffffffffff58(%rbp)
    38d9:	48 89 b5 50 ff ff ff 	mov    %rsi,0xffffffffffffff50(%rbp)
    38e0:	48 89 95 48 ff ff ff 	mov    %rdx,0xffffffffffffff48(%rbp)
    38e7:	48 8b 85 58 ff ff ff 	mov    0xffffffffffffff58(%rbp),%rax
    38ee:	48 8b 50 08          	mov    0x8(%rax),%rdx
    38f2:	48 8b 85 58 ff ff ff 	mov    0xffffffffffffff58(%rbp),%rax
    38f9:	48 8b 40 10          	mov    0x10(%rax),%rax
    38fd:	48 39 c2             	cmp    %rax,%rdx
    3900:	0f 84 f7 00 00 00    	je     39fd <_ZNSt6vectorISsSaISsEE13_M_insert_auxEN9__gnu_cxx17__normal_iteratorIPSsS1_EERKSs+0x137>
    3906:	48 8b 85 58 ff ff ff 	mov    0xffffffffffffff58(%rbp),%rax
    390d:	48 8b 40 08          	mov    0x8(%rax),%rax
    3911:	48 8d 50 f8          	lea    0xfffffffffffffff8(%rax),%rdx
    3915:	48 8b 85 58 ff ff ff 	mov    0xffffffffffffff58(%rbp),%rax
    391c:	48 8b 70 08          	mov    0x8(%rax),%rsi
    3920:	48 8b 85 58 ff ff ff 	mov    0xffffffffffffff58(%rbp),%rax
    3927:	48 89 c7             	mov    %rax,%rdi
    392a:	e8 f1 ec ff ff       	callq  2620 <_ZN9__gnu_cxx13new_allocatorISsE9constructEPSsRKSs@plt>
    392f:	48 8b 85 58 ff ff ff 	mov    0xffffffffffffff58(%rbp),%rax
    3936:	48 8b 40 08          	mov    0x8(%rax),%rax
    393a:	48 8d 50 08          	lea    0x8(%rax),%rdx
    393e:	48 8b 85 58 ff ff ff 	mov    0xffffffffffffff58(%rbp),%rax
    3945:	48 89 50 08          	mov    %rdx,0x8(%rax)
    3949:	48 8b b5 48 ff ff ff 	mov    0xffffffffffffff48(%rbp),%rsi
    3950:	48 8d 7d 80          	lea    0xffffffffffffff80(%rbp),%rdi
    3954:	e8 17 ec ff ff       	callq  2570 <_ZNSsC1ERKSs@plt>
    3959:	48 8b 85 58 ff ff ff 	mov    0xffffffffffffff58(%rbp),%rax
    3960:	48 8b 40 08          	mov    0x8(%rax),%rax
    3964:	48 83 e8 08          	sub    $0x8,%rax
    3968:	48 89 45 98          	mov    %rax,0xffffffffffffff98(%rbp)
    396c:	48 8d 75 98          	lea    0xffffffffffffff98(%rbp),%rsi
    3970:	48 8d 7d 90          	lea    0xffffffffffffff90(%rbp),%rdi
    3974:	e8 07 ee ff ff       	callq  2780 <_ZN9__gnu_cxx17__normal_iteratorIPSsSt6vectorISsSaISsEEEC1ERKS1_@plt>
    3979:	48 8b 85 58 ff ff ff 	mov    0xffffffffffffff58(%rbp),%rax
    3980:	48 8b 40 08          	mov    0x8(%rax),%rax
    3984:	48 83 e8 10          	sub    $0x10,%rax
    3988:	48 89 45 a8          	mov    %rax,0xffffffffffffffa8(%rbp)
    398c:	48 8d 75 a8          	lea    0xffffffffffffffa8(%rbp),%rsi
    3990:	48 8d 7d a0          	lea    0xffffffffffffffa0(%rbp),%rdi
    3994:	e8 e7 ed ff ff       	callq  2780 <_ZN9__gnu_cxx17__normal_iteratorIPSsSt6vectorISsSaISsEEEC1ERKS1_@plt>
    3999:	48 8b 55 90          	mov    0xffffffffffffff90(%rbp),%rdx
    399d:	48 8b 75 a0          	mov    0xffffffffffffffa0(%rbp),%rsi
    39a1:	48 8b bd 50 ff ff ff 	mov    0xffffffffffffff50(%rbp),%rdi
    39a8:	e8 13 ee ff ff       	callq  27c0 <_ZSt13copy_backwardIN9__gnu_cxx17__normal_iteratorIPSsSt6vectorISsSaISsEEEES6_ET0_T_S8_S7_@plt>
    39ad:	48 8d bd 50 ff ff ff 	lea    0xffffffffffffff50(%rbp),%rdi
    39b4:	e8 77 ed ff ff       	callq  2730 <_ZNK9__gnu_cxx17__normal_iteratorIPSsSt6vectorISsSaISsEEEdeEv@plt>
    39b9:	48 89 c7             	mov    %rax,%rdi
    39bc:	48 8d 75 80          	lea    0xffffffffffffff80(%rbp),%rsi
    39c0:	e8 4b ef ff ff       	callq  2910 <_ZNSsaSERKSs@plt>
    39c5:	48 8d 7d 80          	lea    0xffffffffffffff80(%rbp),%rdi
    39c9:	e8 42 ec ff ff       	callq  2610 <_ZNSsD1Ev@plt>
    39ce:	e9 bd 03 00 00       	jmpq   3d90 <_ZNSt6vectorISsSaISsEE13_M_insert_auxEN9__gnu_cxx17__normal_iteratorIPSsS1_EERKSs+0x4ca>
    39d3:	48 89 85 38 ff ff ff 	mov    %rax,0xffffffffffffff38(%rbp)
    39da:	48 8b 9d 38 ff ff ff 	mov    0xffffffffffffff38(%rbp),%rbx
    39e1:	48 8d 7d 80          	lea    0xffffffffffffff80(%rbp),%rdi
    39e5:	e8 26 ec ff ff       	callq  2610 <_ZNSsD1Ev@plt>
    39ea:	48 89 9d 38 ff ff ff 	mov    %rbx,0xffffffffffffff38(%rbp)
    39f1:	48 8b bd 38 ff ff ff 	mov    0xffffffffffffff38(%rbp),%rdi
    39f8:	e8 c3 ee ff ff       	callq  28c0 <_Unwind_Resume@plt>
    39fd:	48 8b bd 58 ff ff ff 	mov    0xffffffffffffff58(%rbp),%rdi
    3a04:	e8 f7 ec ff ff       	callq  2700 <_ZNKSt6vectorISsSaISsEE4sizeEv@plt>
    3a09:	48 89 45 e0          	mov    %rax,0xffffffffffffffe0(%rbp)
    3a0d:	48 8b bd 58 ff ff ff 	mov    0xffffffffffffff58(%rbp),%rdi
    3a14:	e8 57 ea ff ff       	callq  2470 <_ZNKSt6vectorISsSaISsEE8max_sizeEv@plt>
    3a19:	48 3b 45 e0          	cmp    0xffffffffffffffe0(%rbp),%rax
    3a1d:	0f 94 c0             	sete   %al
    3a20:	84 c0                	test   %al,%al
    3a22:	74 0c                	je     3a30 <_ZNSt6vectorISsSaISsEE13_M_insert_auxEN9__gnu_cxx17__normal_iteratorIPSsS1_EERKSs+0x16a>
    3a24:	48 8d 3d 76 04 00 00 	lea    1142(%rip),%rdi        # 3ea1 <_fini+0x39>
    3a2b:	e8 30 ea ff ff       	callq  2460 <_ZSt20__throw_length_errorPKc@plt>
    3a30:	48 83 7d e0 00       	cmpq   $0x0,0xffffffffffffffe0(%rbp)
    3a35:	74 10                	je     3a47 <_ZNSt6vectorISsSaISsEE13_M_insert_auxEN9__gnu_cxx17__normal_iteratorIPSsS1_EERKSs+0x181>
    3a37:	48 8b 45 e0          	mov    0xffffffffffffffe0(%rbp),%rax
    3a3b:	48 01 c0             	add    %rax,%rax
    3a3e:	48 89 85 40 ff ff ff 	mov    %rax,0xffffffffffffff40(%rbp)
    3a45:	eb 0b                	jmp    3a52 <_ZNSt6vectorISsSaISsEE13_M_insert_auxEN9__gnu_cxx17__normal_iteratorIPSsS1_EERKSs+0x18c>
    3a47:	48 c7 85 40 ff ff ff 	movq   $0x1,0xffffffffffffff40(%rbp)
    3a4e:	01 00 00 00 
    3a52:	48 8b 85 40 ff ff ff 	mov    0xffffffffffffff40(%rbp),%rax
    3a59:	48 89 45 e8          	mov    %rax,0xffffffffffffffe8(%rbp)
    3a5d:	48 8b 45 e8          	mov    0xffffffffffffffe8(%rbp),%rax
    3a61:	48 3b 45 e0          	cmp    0xffffffffffffffe0(%rbp),%rax
    3a65:	73 10                	jae    3a77 <_ZNSt6vectorISsSaISsEE13_M_insert_auxEN9__gnu_cxx17__normal_iteratorIPSsS1_EERKSs+0x1b1>
    3a67:	48 8b bd 58 ff ff ff 	mov    0xffffffffffffff58(%rbp),%rdi
    3a6e:	e8 fd e9 ff ff       	callq  2470 <_ZNKSt6vectorISsSaISsEE8max_sizeEv@plt>
    3a73:	48 89 45 e8          	mov    %rax,0xffffffffffffffe8(%rbp)
    3a77:	48 8b bd 58 ff ff ff 	mov    0xffffffffffffff58(%rbp),%rdi
    3a7e:	48 8b 75 e8          	mov    0xffffffffffffffe8(%rbp),%rsi
    3a82:	e8 79 eb ff ff       	callq  2600 <_ZNSt12_Vector_baseISsSaISsEE11_M_allocateEm@plt>
    3a87:	48 89 45 b0          	mov    %rax,0xffffffffffffffb0(%rbp)
    3a8b:	48 8d 75 b0          	lea    0xffffffffffffffb0(%rbp),%rsi
    3a8f:	48 8d bd 70 ff ff ff 	lea    0xffffffffffffff70(%rbp),%rdi
    3a96:	e8 e5 ec ff ff       	callq  2780 <_ZN9__gnu_cxx17__normal_iteratorIPSsSt6vectorISsSaISsEEEC1ERKS1_@plt>
    3a9b:	48 8b 85 70 ff ff ff 	mov    0xffffffffffffff70(%rbp),%rax
    3aa2:	48 89 85 60 ff ff ff 	mov    %rax,0xffffffffffffff60(%rbp)
    3aa9:	48 8b bd 58 ff ff ff 	mov    0xffffffffffffff58(%rbp),%rdi
    3ab0:	e8 6b ea ff ff       	callq  2520 <_ZNSt12_Vector_baseISsSaISsEE19_M_get_Tp_allocatorEv@plt>
    3ab5:	48 89 c6             	mov    %rax,%rsi
    3ab8:	48 8d 7d bf          	lea    0xffffffffffffffbf(%rbp),%rdi
    3abc:	e8 8f ea ff ff       	callq  2550 <_ZNSaISsEC1ERKS_@plt>
    3ac1:	48 8b b5 58 ff ff ff 	mov    0xffffffffffffff58(%rbp),%rsi
    3ac8:	48 8d 7d c0          	lea    0xffffffffffffffc0(%rbp),%rdi
    3acc:	e8 af ec ff ff       	callq  2780 <_ZN9__gnu_cxx17__normal_iteratorIPSsSt6vectorISsSaISsEEEC1ERKS1_@plt>
    3ad1:	48 8d 4d bf          	lea    0xffffffffffffffbf(%rbp),%rcx
    3ad5:	48 8b 95 70 ff ff ff 	mov    0xffffffffffffff70(%rbp),%rdx
    3adc:	48 8b b5 50 ff ff ff 	mov    0xffffffffffffff50(%rbp),%rsi
    3ae3:	48 8b 7d c0          	mov    0xffffffffffffffc0(%rbp),%rdi
    3ae7:	e8 84 ec ff ff       	callq  2770 <_ZSt22__uninitialized_copy_aIN9__gnu_cxx17__normal_iteratorIPSsSt6vectorISsSaISsEEEES6_SsET0_T_S8_S7_SaIT1_E@plt>
    3aec:	48 89 85 60 ff ff ff 	mov    %rax,0xffffffffffffff60(%rbp)
    3af3:	48 8d 7d bf          	lea    0xffffffffffffffbf(%rbp),%rdi
    3af7:	e8 a4 e9 ff ff       	callq  24a0 <_ZNSaISsED1Ev@plt>
    3afc:	48 8d bd 60 ff ff ff 	lea    0xffffffffffffff60(%rbp),%rdi
    3b03:	e8 58 ea ff ff       	callq  2560 <_ZNK9__gnu_cxx17__normal_iteratorIPSsSt6vectorISsSaISsEEE4baseEv@plt>
    3b08:	48 8b 30             	mov    (%rax),%rsi
    3b0b:	48 8b 85 58 ff ff ff 	mov    0xffffffffffffff58(%rbp),%rax
    3b12:	48 89 c7             	mov    %rax,%rdi
    3b15:	48 8b 95 48 ff ff ff 	mov    0xffffffffffffff48(%rbp),%rdx
    3b1c:	e8 ff ea ff ff       	callq  2620 <_ZN9__gnu_cxx13new_allocatorISsE9constructEPSsRKSs@plt>
    3b21:	eb 23                	jmp    3b46 <_ZNSt6vectorISsSaISsEE13_M_insert_auxEN9__gnu_cxx17__normal_iteratorIPSsS1_EERKSs+0x280>
    3b23:	48 89 85 38 ff ff ff 	mov    %rax,0xffffffffffffff38(%rbp)
    3b2a:	48 8b 9d 38 ff ff ff 	mov    0xffffffffffffff38(%rbp),%rbx
    3b31:	48 8d 7d bf          	lea    0xffffffffffffffbf(%rbp),%rdi
    3b35:	e8 66 e9 ff ff       	callq  24a0 <_ZNSaISsED1Ev@plt>
    3b3a:	48 89 9d 38 ff ff ff 	mov    %rbx,0xffffffffffffff38(%rbp)
    3b41:	e9 d1 00 00 00       	jmpq   3c17 <_ZNSt6vectorISsSaISsEE13_M_insert_auxEN9__gnu_cxx17__normal_iteratorIPSsS1_EERKSs+0x351>
    3b46:	48 8d bd 60 ff ff ff 	lea    0xffffffffffffff60(%rbp),%rdi
    3b4d:	e8 0e ec ff ff       	callq  2760 <_ZN9__gnu_cxx17__normal_iteratorIPSsSt6vectorISsSaISsEEEppEv@plt>
    3b52:	48 8b bd 58 ff ff ff 	mov    0xffffffffffffff58(%rbp),%rdi
    3b59:	e8 c2 e9 ff ff       	callq  2520 <_ZNSt12_Vector_baseISsSaISsEE19_M_get_Tp_allocatorEv@plt>
    3b5e:	48 89 c6             	mov    %rax,%rsi
    3b61:	48 8d 7d cf          	lea    0xffffffffffffffcf(%rbp),%rdi
    3b65:	e8 e6 e9 ff ff       	callq  2550 <_ZNSaISsEC1ERKS_@plt>
    3b6a:	48 8b b5 58 ff ff ff 	mov    0xffffffffffffff58(%rbp),%rsi
    3b71:	48 83 c6 08          	add    $0x8,%rsi
    3b75:	48 8d 7d d0          	lea    0xffffffffffffffd0(%rbp),%rdi
    3b79:	e8 02 ec ff ff       	callq  2780 <_ZN9__gnu_cxx17__normal_iteratorIPSsSt6vectorISsSaISsEEEC1ERKS1_@plt>
    3b7e:	48 8d 4d cf          	lea    0xffffffffffffffcf(%rbp),%rcx
    3b82:	48 8b 95 60 ff ff ff 	mov    0xffffffffffffff60(%rbp),%rdx
    3b89:	48 8b 75 d0          	mov    0xffffffffffffffd0(%rbp),%rsi
    3b8d:	48 8b bd 50 ff ff ff 	mov    0xffffffffffffff50(%rbp),%rdi
    3b94:	e8 d7 eb ff ff       	callq  2770 <_ZSt22__uninitialized_copy_aIN9__gnu_cxx17__normal_iteratorIPSsSt6vectorISsSaISsEEEES6_SsET0_T_S8_S7_SaIT1_E@plt>
    3b99:	48 89 85 60 ff ff ff 	mov    %rax,0xffffffffffffff60(%rbp)
    3ba0:	48 8d 7d cf          	lea    0xffffffffffffffcf(%rbp),%rdi
    3ba4:	e8 f7 e8 ff ff       	callq  24a0 <_ZNSaISsED1Ev@plt>
    3ba9:	48 8b bd 58 ff ff ff 	mov    0xffffffffffffff58(%rbp),%rdi
    3bb0:	e8 6b e9 ff ff       	callq  2520 <_ZNSt12_Vector_baseISsSaISsEE19_M_get_Tp_allocatorEv@plt>
    3bb5:	48 89 c6             	mov    %rax,%rsi
    3bb8:	48 8d 7d df          	lea    0xffffffffffffffdf(%rbp),%rdi
    3bbc:	e8 8f e9 ff ff       	callq  2550 <_ZNSaISsEC1ERKS_@plt>
    3bc1:	48 8b bd 58 ff ff ff 	mov    0xffffffffffffff58(%rbp),%rdi
    3bc8:	e8 23 eb ff ff       	callq  26f0 <_ZNSt6vectorISsSaISsEE3endEv@plt>
    3bcd:	48 89 c3             	mov    %rax,%rbx
    3bd0:	48 8b bd 58 ff ff ff 	mov    0xffffffffffffff58(%rbp),%rdi
    3bd7:	e8 f4 e8 ff ff       	callq  24d0 <_ZNSt6vectorISsSaISsEE5beginEv@plt>
    3bdc:	48 89 c7             	mov    %rax,%rdi
    3bdf:	48 8d 55 df          	lea    0xffffffffffffffdf(%rbp),%rdx
    3be3:	48 89 de             	mov    %rbx,%rsi
    3be6:	e8 e5 ea ff ff       	callq  26d0 <_ZSt8_DestroyIN9__gnu_cxx17__normal_iteratorIPSsSt6vectorISsSaISsEEEESsEvT_S7_SaIT0_E@plt>
    3beb:	e9 d5 00 00 00       	jmpq   3cc5 <_ZNSt6vectorISsSaISsEE13_M_insert_auxEN9__gnu_cxx17__normal_iteratorIPSsS1_EERKSs+0x3ff>
    3bf0:	48 89 85 38 ff ff ff 	mov    %rax,0xffffffffffffff38(%rbp)
    3bf7:	48 8b 9d 38 ff ff ff 	mov    0xffffffffffffff38(%rbp),%rbx
    3bfe:	48 8d 7d cf          	lea    0xffffffffffffffcf(%rbp),%rdi
    3c02:	e8 99 e8 ff ff       	callq  24a0 <_ZNSaISsED1Ev@plt>
    3c07:	48 89 9d 38 ff ff ff 	mov    %rbx,0xffffffffffffff38(%rbp)
    3c0e:	eb 07                	jmp    3c17 <_ZNSt6vectorISsSaISsEE13_M_insert_auxEN9__gnu_cxx17__normal_iteratorIPSsS1_EERKSs+0x351>
    3c10:	48 89 85 38 ff ff ff 	mov    %rax,0xffffffffffffff38(%rbp)
    3c17:	48 8b bd 38 ff ff ff 	mov    0xffffffffffffff38(%rbp),%rdi
    3c1e:	e8 4d ec ff ff       	callq  2870 <__cxa_begin_catch@plt>
    3c23:	48 8b bd 58 ff ff ff 	mov    0xffffffffffffff58(%rbp),%rdi
    3c2a:	e8 f1 e8 ff ff       	callq  2520 <_ZNSt12_Vector_baseISsSaISsEE19_M_get_Tp_allocatorEv@plt>
    3c2f:	48 89 c6             	mov    %rax,%rsi
    3c32:	48 8d 7d de          	lea    0xffffffffffffffde(%rbp),%rdi
    3c36:	e8 15 e9 ff ff       	callq  2550 <_ZNSaISsEC1ERKS_@plt>
    3c3b:	48 8d 55 de          	lea    0xffffffffffffffde(%rbp),%rdx
    3c3f:	48 8b b5 60 ff ff ff 	mov    0xffffffffffffff60(%rbp),%rsi
    3c46:	48 8b bd 70 ff ff ff 	mov    0xffffffffffffff70(%rbp),%rdi
    3c4d:	e8 7e ea ff ff       	callq  26d0 <_ZSt8_DestroyIN9__gnu_cxx17__normal_iteratorIPSsSt6vectorISsSaISsEEEESsEvT_S7_SaIT0_E@plt>
    3c52:	48 8d 7d de          	lea    0xffffffffffffffde(%rbp),%rdi
    3c56:	e8 45 e8 ff ff       	callq  24a0 <_ZNSaISsED1Ev@plt>
    3c5b:	48 8d bd 70 ff ff ff 	lea    0xffffffffffffff70(%rbp),%rdi
    3c62:	e8 f9 e8 ff ff       	callq  2560 <_ZNK9__gnu_cxx17__normal_iteratorIPSsSt6vectorISsSaISsEEE4baseEv@plt>
    3c67:	48 8b 30             	mov    (%rax),%rsi
    3c6a:	48 8b bd 58 ff ff ff 	mov    0xffffffffffffff58(%rbp),%rdi
    3c71:	48 8b 55 e8          	mov    0xffffffffffffffe8(%rbp),%rdx
    3c75:	e8 26 e9 ff ff       	callq  25a0 <_ZNSt12_Vector_baseISsSaISsEE13_M_deallocateEPSsm@plt>
    3c7a:	e8 81 e8 ff ff       	callq  2500 <__cxa_rethrow@plt>
    3c7f:	48 89 85 38 ff ff ff 	mov    %rax,0xffffffffffffff38(%rbp)
    3c86:	48 8b 9d 38 ff ff ff 	mov    0xffffffffffffff38(%rbp),%rbx
    3c8d:	48 8d 7d de          	lea    0xffffffffffffffde(%rbp),%rdi
    3c91:	e8 0a e8 ff ff       	callq  24a0 <_ZNSaISsED1Ev@plt>
    3c96:	48 89 9d 38 ff ff ff 	mov    %rbx,0xffffffffffffff38(%rbp)
    3c9d:	eb 07                	jmp    3ca6 <_ZNSt6vectorISsSaISsEE13_M_insert_auxEN9__gnu_cxx17__normal_iteratorIPSsS1_EERKSs+0x3e0>
    3c9f:	48 89 85 38 ff ff ff 	mov    %rax,0xffffffffffffff38(%rbp)
    3ca6:	48 8b 9d 38 ff ff ff 	mov    0xffffffffffffff38(%rbp),%rbx
    3cad:	e8 7e eb ff ff       	callq  2830 <__cxa_end_catch@plt>
    3cb2:	48 89 9d 38 ff ff ff 	mov    %rbx,0xffffffffffffff38(%rbp)
    3cb9:	48 8b bd 38 ff ff ff 	mov    0xffffffffffffff38(%rbp),%rdi
    3cc0:	e8 fb eb ff ff       	callq  28c0 <_Unwind_Resume@plt>
    3cc5:	48 8d 7d df          	lea    0xffffffffffffffdf(%rbp),%rdi
    3cc9:	e8 d2 e7 ff ff       	callq  24a0 <_ZNSaISsED1Ev@plt>
    3cce:	48 8b 85 58 ff ff ff 	mov    0xffffffffffffff58(%rbp),%rax
    3cd5:	48 8b 40 10          	mov    0x10(%rax),%rax
    3cd9:	48 89 c2             	mov    %rax,%rdx
    3cdc:	48 8b 85 58 ff ff ff 	mov    0xffffffffffffff58(%rbp),%rax
    3ce3:	48 8b 00             	mov    (%rax),%rax
    3ce6:	48 89 d1             	mov    %rdx,%rcx
    3ce9:	48 29 c1             	sub    %rax,%rcx
    3cec:	48 89 c8             	mov    %rcx,%rax
    3cef:	48 c1 f8 03          	sar    $0x3,%rax
    3cf3:	48 89 c2             	mov    %rax,%rdx
    3cf6:	48 8b 85 58 ff ff ff 	mov    0xffffffffffffff58(%rbp),%rax
    3cfd:	48 8b 30             	mov    (%rax),%rsi
    3d00:	48 8b bd 58 ff ff ff 	mov    0xffffffffffffff58(%rbp),%rdi
    3d07:	e8 94 e8 ff ff       	callq  25a0 <_ZNSt12_Vector_baseISsSaISsEE13_M_deallocateEPSsm@plt>
    3d0c:	48 8d bd 70 ff ff ff 	lea    0xffffffffffffff70(%rbp),%rdi
    3d13:	e8 48 e8 ff ff       	callq  2560 <_ZNK9__gnu_cxx17__normal_iteratorIPSsSt6vectorISsSaISsEEE4baseEv@plt>
    3d18:	48 8b 10             	mov    (%rax),%rdx
    3d1b:	48 8b 85 58 ff ff ff 	mov    0xffffffffffffff58(%rbp),%rax
    3d22:	48 89 10             	mov    %rdx,(%rax)
    3d25:	48 8d bd 60 ff ff ff 	lea    0xffffffffffffff60(%rbp),%rdi
    3d2c:	e8 2f e8 ff ff       	callq  2560 <_ZNK9__gnu_cxx17__normal_iteratorIPSsSt6vectorISsSaISsEEE4baseEv@plt>
    3d31:	48 8b 10             	mov    (%rax),%rdx
    3d34:	48 8b 85 58 ff ff ff 	mov    0xffffffffffffff58(%rbp),%rax
    3d3b:	48 89 50 08          	mov    %rdx,0x8(%rax)
    3d3f:	48 8d bd 70 ff ff ff 	lea    0xffffffffffffff70(%rbp),%rdi
    3d46:	e8 15 e8 ff ff       	callq  2560 <_ZNK9__gnu_cxx17__normal_iteratorIPSsSt6vectorISsSaISsEEE4baseEv@plt>
    3d4b:	48 8b 10             	mov    (%rax),%rdx
    3d4e:	48 8b 45 e8          	mov    0xffffffffffffffe8(%rbp),%rax
    3d52:	48 c1 e0 03          	shl    $0x3,%rax
    3d56:	48 01 c2             	add    %rax,%rdx
    3d59:	48 8b 85 58 ff ff ff 	mov    0xffffffffffffff58(%rbp),%rax
    3d60:	48 89 50 10          	mov    %rdx,0x10(%rax)
    3d64:	eb 2a                	jmp    3d90 <_ZNSt6vectorISsSaISsEE13_M_insert_auxEN9__gnu_cxx17__normal_iteratorIPSsS1_EERKSs+0x4ca>
    3d66:	48 89 85 38 ff ff ff 	mov    %rax,0xffffffffffffff38(%rbp)
    3d6d:	48 8b 9d 38 ff ff ff 	mov    0xffffffffffffff38(%rbp),%rbx
    3d74:	48 8d 7d df          	lea    0xffffffffffffffdf(%rbp),%rdi
    3d78:	e8 23 e7 ff ff       	callq  24a0 <_ZNSaISsED1Ev@plt>
    3d7d:	48 89 9d 38 ff ff ff 	mov    %rbx,0xffffffffffffff38(%rbp)
    3d84:	48 8b bd 38 ff ff ff 	mov    0xffffffffffffff38(%rbp),%rdi
    3d8b:	e8 30 eb ff ff       	callq  28c0 <_Unwind_Resume@plt>
    3d90:	48 81 c4 c8 00 00 00 	add    $0xc8,%rsp
    3d97:	5b                   	pop    %rbx
    3d98:	c9                   	leaveq 
    3d99:	c3                   	retq   

0000000000003d9a <_ZNSt6vectorISsSaISsEE9push_backERKSs>:
    3d9a:	55                   	push   %rbp
    3d9b:	48 89 e5             	mov    %rsp,%rbp
    3d9e:	48 83 ec 10          	sub    $0x10,%rsp
    3da2:	48 89 7d f8          	mov    %rdi,0xfffffffffffffff8(%rbp)
    3da6:	48 89 75 f0          	mov    %rsi,0xfffffffffffffff0(%rbp)
    3daa:	48 8b 45 f8          	mov    0xfffffffffffffff8(%rbp),%rax
    3dae:	48 8b 50 08          	mov    0x8(%rax),%rdx
    3db2:	48 8b 45 f8          	mov    0xfffffffffffffff8(%rbp),%rax
    3db6:	48 8b 40 10          	mov    0x10(%rax),%rax
    3dba:	48 39 c2             	cmp    %rax,%rdx
    3dbd:	74 2e                	je     3ded <_ZNSt6vectorISsSaISsEE9push_backERKSs+0x53>
    3dbf:	48 8b 45 f8          	mov    0xfffffffffffffff8(%rbp),%rax
    3dc3:	48 8b 70 08          	mov    0x8(%rax),%rsi
    3dc7:	48 8b 45 f8          	mov    0xfffffffffffffff8(%rbp),%rax
    3dcb:	48 89 c7             	mov    %rax,%rdi
    3dce:	48 8b 55 f0          	mov    0xfffffffffffffff0(%rbp),%rdx
    3dd2:	e8 49 e8 ff ff       	callq  2620 <_ZN9__gnu_cxx13new_allocatorISsE9constructEPSsRKSs@plt>
    3dd7:	48 8b 45 f8          	mov    0xfffffffffffffff8(%rbp),%rax
    3ddb:	48 8b 40 08          	mov    0x8(%rax),%rax
    3ddf:	48 8d 50 08          	lea    0x8(%rax),%rdx
    3de3:	48 8b 45 f8          	mov    0xfffffffffffffff8(%rbp),%rax
    3de7:	48 89 50 08          	mov    %rdx,0x8(%rax)
    3deb:	eb 19                	jmp    3e06 <_ZNSt6vectorISsSaISsEE9push_backERKSs+0x6c>
    3ded:	48 8b 7d f8          	mov    0xfffffffffffffff8(%rbp),%rdi
    3df1:	e8 fa e8 ff ff       	callq  26f0 <_ZNSt6vectorISsSaISsEE3endEv@plt>
    3df6:	48 89 c6             	mov    %rax,%rsi
    3df9:	48 8b 55 f0          	mov    0xfffffffffffffff0(%rbp),%rdx
    3dfd:	48 8b 7d f8          	mov    0xfffffffffffffff8(%rbp),%rdi
    3e01:	e8 ca e7 ff ff       	callq  25d0 <_ZNSt6vectorISsSaISsEE13_M_insert_auxEN9__gnu_cxx17__normal_iteratorIPSsS1_EERKSs@plt>
    3e06:	c9                   	leaveq 
    3e07:	c3                   	retq   

0000000000003e08 <_ZN4Test6addSthERKSs>:
    3e08:	55                   	push   %rbp
    3e09:	48 89 e5             	mov    %rsp,%rbp
    3e0c:	48 83 ec 10          	sub    $0x10,%rsp
    3e10:	48 89 7d f8          	mov    %rdi,0xfffffffffffffff8(%rbp)
    3e14:	48 89 75 f0          	mov    %rsi,0xfffffffffffffff0(%rbp)
    3e18:	48 8b 7d f8          	mov    0xfffffffffffffff8(%rbp),%rdi
    3e1c:	48 8b 75 f0          	mov    0xfffffffffffffff0(%rbp),%rsi
    3e20:	e8 2b e9 ff ff       	callq  2750 <_ZNSt6vectorISsSaISsEE9push_backERKSs@plt>
    3e25:	c9                   	leaveq 
    3e26:	c3                   	retq   
    3e27:	90                   	nop    
    3e28:	90                   	nop    
    3e29:	90                   	nop    
    3e2a:	90                   	nop    
    3e2b:	90                   	nop    
    3e2c:	90                   	nop    
    3e2d:	90                   	nop    
    3e2e:	90                   	nop    
    3e2f:	90                   	nop    

0000000000003e30 <__do_global_ctors_aux>:
    3e30:	55                   	push   %rbp
    3e31:	48 89 e5             	mov    %rsp,%rbp
    3e34:	53                   	push   %rbx
    3e35:	48 8d 1d d4 11 20 00 	lea    2101716(%rip),%rbx        # 205010 <__CTOR_LIST__+0x10>
    3e3c:	48 83 ec 08          	sub    $0x8,%rsp
    3e40:	48 8b 05 c9 11 20 00 	mov    2101705(%rip),%rax        # 205010 <__CTOR_LIST__+0x10>
    3e47:	48 83 f8 ff          	cmp    $0xffffffffffffffff,%rax
    3e4b:	74 12                	je     3e5f <__do_global_ctors_aux+0x2f>
    3e4d:	0f 1f 00             	nopl   (%rax)
    3e50:	48 83 eb 08          	sub    $0x8,%rbx
    3e54:	ff d0                	callq  *%rax
    3e56:	48 8b 03             	mov    (%rbx),%rax
    3e59:	48 83 f8 ff          	cmp    $0xffffffffffffffff,%rax
    3e5d:	75 f1                	jne    3e50 <__do_global_ctors_aux+0x20>
    3e5f:	48 83 c4 08          	add    $0x8,%rsp
    3e63:	5b                   	pop    %rbx
    3e64:	c9                   	leaveq 
    3e65:	c3                   	retq   
    3e66:	90                   	nop    
    3e67:	90                   	nop    
Disassembly of section .fini:

0000000000003e68 <_fini>:
    3e68:	48 83 ec 08          	sub    $0x8,%rsp
    3e6c:	e8 0f eb ff ff       	callq  2980 <__do_global_dtors_aux>
    3e71:	48 83 c4 08          	add    $0x8,%rsp
    3e75:	c3                   	retq   
