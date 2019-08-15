Postgres  top level key function call.

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
										grouping_planner()
										SS_identify_outer_params()
										SS_charge_for_initplans()
									}
									create_plan(PlannerInfo){

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
							}
						}
					}
				}
			}
		}
	}
}
