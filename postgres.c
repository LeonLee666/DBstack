Postgres-backend  top-level function call stack.

main(){  //pg程序入口 backend/main/main.c
	PostmasterMain(){   // postmaster 入口
		Serverloop(){    // select 监听			
			BackendStartup(){    // each session startup a new process
				pid = fork_process();  // fork的子进程调用BackendRun,内部接着调用PostgresMain
				PostgresMain(){      // backend 入口
					ReadCommand()    // 获取sql string
					exec_simple_query(char* sql[]){     // 执行DML查询
						start_xact_command(){
							StartTransactionCommand() {
								StartTransaction()   // 启动事务
							}
						}
						parsetree_list pg_parse_query(){
							raw_parser(){    // parse

							}
						}
						for each parsetree_list {  // 每个parse tree优化、计划、执行	
							start_xact_command()    // Make sure we are in a transaction command
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
									standard_planner(){   //hook
										PlannerInfo subquery_planner(){   //优化入口
											SS_process_ctes()   //cte 语法处理
											pull_up_sublinks()   // 上提子连接 （any exist 从句）
											pull_up_subqueries()  // 上提子查询
											flatten_simple_union_all()  // 优化sql中union all操作
											preprocess_rowmarks() 
											expand_inherited_tables()
											preprocess_expression()  // 条件化简
											preprocess_qual_conditions()
											remove_useless_groupby_columns()
											reduce_outer_joins()
											grouping_planner(){    // 处理非SPJ语句并生成物理计划
												query_planner(){  // 物理计划生成入口。hook
													setup_simple_rel_arrays()  // 找到所有基表
													add_base_rels_to_query()   // 生成所有基表的优化信息RelOptInfo
													build_base_rel_tlists()    // RelOptInfo绑定目标列和条件从句
													deconstruct_jointree()	 // 【重要】join tree分解拉平
													make_outerjoininfo()
													RelOptInfo make_one_rel(PlannerInfo){  // 【重要】物理优化, 生成路径
														set_base_rel_sizes(){   // RangeTblEntry选择率估计等
															set_rel_size(){
																set_baserel_size_estimates()
															}
														}													
														set_base_rel_pathlist(){  //针对RangeTblEntry的单表查询路径选择问题：顺序扫描，索引扫描或tid扫描
															set_plain_rel_pathlist(){
																set_cheapest()    //选取三种路径最优的一种
															}
														}
														make_rel_from_joinlist(){   // 多表join的路径选择： 动态规划或遗传算法
															standard_join_search()
														}
													}											
												}
											}
											SS_identify_outer_params()
											SS_charge_for_initplans()
										}
										create_plan(PlannerInfo){
											create_scan_plan(){   // 根据path生成对应的plan tree
												create_seqscan_plan()
												create_samplescan_plan()
												create_indexscan_plan()
												create_bitmap_scan_plan()
												create_tidscan_plan()
												create_subqueryscan_plan()
												create_functionscan_plan()
												create_tablefuncscan_plan()
												create_valuesscan_plan()
												create_ctescan_plan()
												create_namedtuplestorescan_plan()
												create_worktablescan_plan()
												......
											}
											create_join_plan()
										}

										SS_finalize_plan(){

										}
									}
								}
							}

							CreatePortal()
							PortalDefineQuery()
							PortalStart() {
								CreateQueryDesc(){
									ExecutorStart(){
										//
									}
								}
							}
							PortalRun(){
								PortalRunSelect(){
									standard_executorRun(){   // 执行器入口
										executePlan(){
											ExecProcNode(){
												ExecLockRows()
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
						}
						finish_xact_command(){
							CommitTransactionCommand(){
								CommitTransaction(){ // 提交事务
									RecordTransactionCommit()  // 日志落盘
									LockReleaseAll()   // 锁释放
								}  // 提交事务
							}
						}
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
