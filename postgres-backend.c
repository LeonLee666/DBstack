Postgres-backend  top level function-tree.

main(){  //程序入口
	PostmasterMain(){   // master 入口
		Serverloop(){    // select 监听
			BackendStartup(){    // each session startup a new process
				PostgresMain(){      // backend 入口
					ReadCommand()    // 获取sql string
					exec_simple_query(){     // 执行DML查询
						start_xact_command()
						pg_parse_query(){
							raw_parser()    // parse
						}
						pg_analyze_and_rewrite(){
							parse_analyze(){
								transformSelectStmt() {
									transformFromClause()
									transformTargetList()
								}
							}
							parse_rewrite_query(){
								QueryRewrite()
							}
						}

						pg_plan_queries(){
							pg_plan_query(){
								standard_planner(){
									PlannerInfo subquery_planner(){
										SS_process_ctes()
										pull_up_sublinks()
										pull_up_subqueries()
										flatten_simple_union_all()
										preprocess_rowmarks()
										expand_inherited_tables()
										preprocess_expression()
										preprocess_qual_conditions()
										remove_useless_groupby_columns()
										reduce_outer_joins()
										grouping_planner(){
											query_planner(){
												deconstruct_jointree()	
												make_outerjoininfo()
												RelOptInfo make_one_rel(PlannerInfo){
													set_rel_size(){
														cost_qual_eval()
													}
													set_rel_pathlist(){
														set_plain_rel_pathlist(){
															add_path(create_seqscan_path())
														}
													}
													make_rel_from_joinlist(){

													}
												}											
											}
										}
										SS_identify_outer_params()
										SS_charge_for_initplans()
									}
									create_plan(PlannerInfo){
										create_scan_plan()
										create_join_plan()
									}

									SS_finalize_plan(){

									}
								}
							}
						}

						CreatePortal()
						PortalDefineQuery()
						PortalStart()




						PortalRun(){
							PortalRunSelect(){
								standard_executorRun(){
									executePlan(){
										ExecProcNode(){
											ExecScan(){
												SeqNext(){
													......
												}
											}
										}
									}
								}
							}


							PortalRunMulti(){
								ProcessQuery(){
									standard_executorRun(){
										executePlan(){
											ExecProcNode(){
												ExecModifyTable(){
													ExecInsert(){
														heap_insert(){
															RelationPutHeapTuple(){
																PageAddItemExtended(){

																}
															}
														}
													}
												}
											}
										}
									}
								}

								PortalRunUtility(){
									standard_ProcessUtility(){
										ExecVacuum(){
											vacuum(){
												analyze_rel(){
													do_analyze_rel(){
														acquire_sample_rows()
													}
												}
											}
										}
									}
								}
							}
						}

						PortalDrop()

						finish_xact_command()
						EndCommand()
					}
				}
			}


			SysLogger_Start()
			StartBackgroundWriter()
			StartWalWriter()
			StartAutoVacLauncher()
			pgarch_start()
			pgstat_start()
		}
	}
}
