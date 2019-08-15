Postgres-backend  top level key function call.

main(){
	PostmasterMain(){
		Serverloop(){
			BackendStartup(){
				PostgreMain(){
					exec_simple_query(){

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
					}
				}
			}
		}
	}
}
