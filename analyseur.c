#include "analyseur.h"
#define synErrSize 30
extern int yylex();
extern char* yytext; // it's a solution to get a String as a token 
extern int yylineno;
// used variables :
typetoken token ;
syntaxErr *synErr[synErrSize];
boolean follow_token = false;

// _lire_token()
typetoken _lire_token(){
	if(follow_token){
		follow_token =false;
		return token; //renvoie du token déjà lu !
	}
	else{
		return (typetoken)yylex();
	}
}
// _const : numbre | true | false ; 
boolean _const() {
	boolean resultat=false;
	if(token==NUM){
		resultat=true;
	}
	else if(token==IDF){ // can be used with different ways here the constant will be a string IDF here gonna be a string
		resultat=true;
	}
	else{
		resultat=false;
	}
	return resultat;
}
// _type : integer | natural | float | char | string ;
boolean _type() {
	boolean result;
	result=false;
	if(token==INTEGER)
		result = true;
	else if(token==NATURAL)
		result=true;
	else if(token==FLOAT)
		result=true;
	else if(token==CHAR)
		result=true;
	else if(token==STRING)
		result=true;
	else
		result = false;
	return result;
}

boolean _gnat_ads(){
	boolean result;
	/*
		TYPE IDF IS NEW _type() PT_COMMA
					| PRIVATE PT_COMMA
	*/
	if(token==TYPE){
		token=_lire_token();
		if(token==IDF){
			token=_lire_token();
			if(token==IS){
				token=_lire_token();
				if(token==PRIVATE){
					token=_lire_token();
					if(token==PT_COMMA){
						result=true;
					}
					else{
						result=false;
					} 
				}
				else if(token==NEW){
					token=_lire_token();
					if(_type()){
						token=_lire_token();
						if(token==PT_COMMA)
							result=true;
						else{result=false;}
					}else{result=false;}
				}
				else{
					result=false;
				} 
			}
			else {
				result=false;
			}
		}
		else {
			result=false;
		}
	}
	/* 
		CONSTANT IDF PT_ASSIGN _type() PT_COMMA
									   | AFFECT _const() PT_COMMA
	*/
	else if(token==CONSTANT){
		token=_lire_token();
		if(token==IDF){
			token=_lire_token();
			if(token==PT_ASSIGN){
				token=_lire_token();
				if(_type()){
					token=_lire_token();
					if(token==PT_COMMA){
						result=true;
					}
					else if(token==AFFECT){
						token=_lire_token();
						if(token==_const()){
							token=_lire_token();
							if(token==PT_COMMA){
								result=true;
							}
							else{
								result=false;
							}
						}else{
							result=false;
						}
					}else{
						result=false;
					}
				}else{
					result=false;
				}
			}else{
				result=false;
			}
		}
	}/*
		IDF PT_ASSIGN _type() PT_COMMA
					| AFFECT _const() PT_COMMA
	*/
	else if(token==IDF){
			token=_lire_token();
			if(token==PT_ASSIGN){
				token=_lire_token();
				if(_type()){
					token=_lire_token();
					if(token==PT_COMMA){
						result=true;
					}
					else if(token==AFFECT){
						token=_lire_token();
						if(token==_const()){
							token=_lire_token();
							if(token==PT_COMMA){
								result=true;
							}
							else{
								result=false;
							}
						}else{
							result=false;
						}
					}else{
						result=false;
					}
				}else{
					result=false;
				}
			}else{
				result=false;
			}
	}
	///////////////////////////////////////////////
	/*
		PACK IDF WITH SPARK_Mode IS
	*/
	else if(token==PACK){
		token=_lire_token();
		if(token==IDF){
			token=_lire_token();
			if(token==WITH){
				token=_lire_token();
				if (token==SPARK_Mode){
					token=_lire_token();
					if(token==IS){
						result=true;
					}
					else result=false;
				}
				else{
					// une erreur sémantique
					result=false;
				} 
			}
			else result=false;
		}
		else result=false;
	}
	/*
		WITH IDFPACK USE IDFPACK PT_COMMA
				 | COMMA IDFPACK USE IDFPACK PT_COMMA
	*/
	else if(token==WITH){
		token=_lire_token();
		if(token==IDFPACK){
			token=_lire_token();
			if(token==PT_COMMA){
				token=_lire_token();
				if(token==USE){
					token=_lire_token();
					if(token==IDFPACK){
						token=_lire_token();
						if(token==PT_COMMA){
							result=true;
						}else{result=false;}
					}else{result=false;}
				}else{result=false;}
			}else{result=false;}
		}else{result=false;}
	}
	/*
		FUNC IDF RETURN IDF PT_COMMA
				 | POPEN IDF PT_ASSIGN IN IDF PCLOSE RETURN IDF PT_COMMA
	*/
	else if(token==FUNC){
		token=_lire_token();
		if(token==IDF){
			token=_lire_token();
			if(token==RETURN){
				token=_lire_token();
				if(token==IDF){
					token=_lire_token();
					if(token==PT_COMMA)
						result=true;
					else{result=false;}
				}else{result=false;}
				///////////////////////////////
			}else if(token==POPEN){
				token=_lire_token();
				if(token==IDF){
					// we gotta test if this IDF is already declared as a type or not
					token=_lire_token();
					if(token==PT_ASSIGN){
						token=_lire_token();
						if(token==IN){
							token=_lire_token();
							if(token==IDF){
								token=_lire_token();
								if(token==PCLOSE){
									token=_lire_token();
									if(token==RETURN){
										token=_lire_token();
										if(token==IDF){
											token=_lire_token();
											if(token==PT_COMMA)
												result=true;
											else {result=false;}
										}else{result=false;}
									}else{result=false;}
								}else{result=false;}
							}else if(token==OUT){
								// a semantique error
								result=false;
							}
						}else if(token==OUT){
							// semantic error in Spark
						}
					}else{result=false;}
				}else{result=false;}
			}else{result=false;}
		}else{result=false;}
	}
	/*
		PROC IDF POPEN PT_ASSIGN IN IDF PCLOSE PT_COMMA
	*/
	else if(token==PROC){
		token=_lire_token();
		if(token==IDF){
			token=_lire_token();
			if(token==POPEN){
				token=_lire_token();
				if(token==IDF){
					token=_lire_token();
					if(token==PT_ASSIGN){
						token=_lire_token();
						if(token==IN){
							token=_lire_token();
							if(token==IDF){
								// this IDF is gonna define a type , so we gotta test if it's already declared
								token=_lire_token();
								if(token==PCLOSE){
									token=_lire_token();
									if(token==PT_COMMA)
										result=true;
									else{result=false;}
								}else{result=false;}

							}else if(token==OUT){
								printf("a semantic error which is against Gnatprove rules : %s at the line %d \n",yytext,yylineno);
								result=false;
							}
						}else if(token==OUT){
							printf("a semantic error which is against Gnatprove rules : %s at the line %d \n",yytext,yylineno);
							result=false;
						}else{result=false;}
					}else if(token==COMMA){
						// like gonna make a series of declaration 
						result=true; // till now, until we add its code
					}else{result=false;}
				}else{result=false;}
			}else{result=false;}
		}else{result=false;}
	}

	else {result=false;}
	return result;
}

// _list_gnat_ads :
boolean _list_gnat_ads(){
	boolean result=false;
	while(token!=END){
		if(_gnat_ads()){
			result=true;
		}else{
			result=false;printf("Une erreur syntaxique dans la ligne : %d",yylineno); break;
		}
		token=_lire_token();
	}
	return result;
}

////////////////////////////// from here begins the .adb code : /////////////////////////////
boolean _gnat_adb(){
	boolean result=false;
	/*
		WITH IDFPACK PT_COMMA USE IDFPACK PT_COMMA
	*/
	if(token==WITH){
		token=_lire_token();
		if(token==IDFPACK){
			token=_lire_token();
			if(token==PT_COMMA){
				token=_lire_token();
				if(token==USE){
					token=_lire_token();
					if(token==IDFPACK){
						token=_lire_token();
						if(token==PT_COMMA)
							result=true;
						else{result=false;}
					}
				}else{result=false;}//gotta print "USE keyword is missing"
			}else{result=false;}//normally there should be a possibility to import a lot of packages
		}else{result=false;}
	}
	/*
		PACK IDF IS 
			 |BODY IDF IS
	*/
	else if(token==PACK){
		token=_lire_token();
		if(token==IDF){
			token=_lire_token();
			if(token==IS){
				result=true;
			}else{result=false;}
		}else if(token==BODY){
			token=_lire_token();
			if(token==IDF){
				token=_lire_token();
				if(token==IS)
					result=true;
				else{result=false;}
			}else{result=false;}
		}else{result=false;}
	}
	/*
		END IDF PT_COMMA
	*/
	else if(token==END){
		token=_lire_token();
		if(token==IDF){
			token=_lire_token();
			if(token==PT_COMMA)
				result=true;
			else{result=false;}
		}else{result=false;}
	}
	/*
		FUNC IDF POPEN IDF PT_ASSIGN _type() PCLOSE RETURN _type() IS _list_decl_adb() BEG_IN _list_inst_adb() RETURN IDF PT_COMMA END IDF PT_COMMA
				 | RETURN _type() IS _list_decl_adb() BEG_IN _list_inst_adb() RETURN IDF PT_COMMA END IDF PT_COMMA
	*/
	else if(token==FUNC){
		token=_lire_token();
		if(token==IDF){
			token=_lire_token();
			if(token==POPEN){
				token=_lire_token();
				if(token==IDF){
					token=_lire_token();
					if(token==PT_ASSIGN){
						token=_lire_token();
						if(token==IN){
							token=_lire_token();
							if(_type()){ // normally we can have a lot of parameters
								token=_lire_token();
								if(token==PCLOSE){
									token=_lire_token();
									if(token==RETURN){
										token=_lire_token();
										if(_type()){
											token=_lire_token();
											if(token==IS){
												token=_lire_token();
												if(_list_decl_adb()){
													token=_lire_token();
													if(token==BEG_IN){
														token=_lire_token();
														if(_list_inst_adb()){
															token=_lire_token();
															if(token==RETURN){
																token=_lire_token();
																if(token==IDF){// we gotta test if this var has the same type as the function returns
																	token=_lire_token();
																	if(token==PT_COMMA){
																		token=_lire_token();
																		if(token==END){
																			token=_lire_token();
																			if(token==IDF){// we gotta test if it's the same name as the function
																				token=_lire_token();
																				if(token==PT_COMMA)
																					result=true;
																			}else{result=false;/*and this has to give a semantic error*/}
																		}else{result=false;}// normally we can have a lot of functions
																	}else{result=false;}
																}else{result=false;} 
															}else{result=false;}
														}else{result=false;}
													}else{result=false;}
												}else{result=false;}
											}else{result=false;}
										}else{result=false;}
									}else{result=false;}
								}else{result=false;} // but we've to be able to have a lot of parameters 
							}else if(token==OUT){
								result=true; // but a semantique error
							}else{result=false;}
						}else if(token==OUT){
							result=true;// but a semantique error
						}else{result=false;}
					}else{result=false;}
				}else{result=false;}
			}else if(token==RETURN){ // in case of a function without parameters
				token=_lire_token();
				if(_type()){
					// gotta repeate the same 
					token=_lire_token();
					if(token==IS){
						token=_lire_token();
						if(_list_decl_adb()){
							token=_lire_token();
							if(token==BEG_IN){
								token=_lire_token();
								if(_list_inst_adb()){
									token=_lire_token();
									if(token==RETURN){
										token=_lire_token();
										if(token==IDF){// we gotta test if this var has the same type as the function returns
											token=_lire_token();
											if(token==PT_COMMA){
												token=_lire_token();
												if(token==END){
													token=_lire_token();
													if(token==IDF){// we gotta test if it's the same name as the function
														token=_lire_token();
														if(token==PT_COMMA)
															result=true;
														else{result=false;}
													}else{result=false;/*and this has to give a semantic error*/}
												}else{result=false;}// normally we can have a lot of functions
											}else{result=false;}
										}else{result=false;} 
									}else{result=false;}
								}else{result=false;}
							}else{result=false;}
						}else{result=false;}
					}else{result=false;}
				//////
				}else{result=false;/*une erreur sémantique à revoir*/}
			}else{result=false;}
		}else{result=false;}
	}
	/*
		
	*/
	/////////
	else {result=false;}
	return result;
}
/// __decl_adb()
boolean __decl_adb(){
	boolean result =false;
	/*
		IDF PT_ASSIGN _type() PT_COMMA
							  | AFFECT _const() PT_COMMA
	*/
	if(token==IDF){
		token=_lire_token();
			if(token==PT_ASSIGN){
				token=_lire_token();
				if(_type()){
					token=_lire_token();
					if(token==PT_COMMA){
						result=true;
					}
					else if(token==AFFECT){
						token=_lire_token();
						if(token==_const()){
							token=_lire_token();
							if(token==PT_COMMA){
								result=true;
							}
							else{
								result=false;
							}
						}else{
							result=false;
						}
					}else{
						result=false;
					}
				}else{
					result=false;
				}
			}else{
				result=false;
			}
	}
	/*
		CONSTANT IDF PT_ASSIGN _type() PT_COMMA
									   | AFFECT _const() PT_COMMA
	*/
	else if(token==CONSTANT){
		token=_lire_token();
		if(token==IDF){
			token=_lire_token();
			if(token==PT_ASSIGN){
				token=_lire_token();
				if(_type()){
					token=_lire_token();
					if(token==PT_COMMA){
						result=true;
					}
					else if(token==AFFECT){
						token=_lire_token();
						if(token==_const()){
							token=_lire_token();
							if(token==PT_COMMA){
								result=true;
							}
							else{
								result=false;
							}
						}else{
							result=false;
						}
					}else{
						result=false;
					}
				}else{
					result=false;
				}
			}else{
				result=false;
			}
		}
	}
	/*
		
	*/
	////
	else {result=false;}
	return result;
}
// _list_decl_adb()
boolean _list_decl_adb(){
	boolean result=false;
	while(token!=BEG_IN){
		if(__decl_adb()){
			continue;
		}else{
			result=false;break;
		}
		token=_lire_token();
	}
	return result;
}
// _inst_adb()
boolean _inst_adb(){
	boolean result=false;
}
//////////////////////////////////////////////////////////////////////////////////////////////
// main()
int main(int argc, char const *argv[])
{	
	token=_lire_token();
	if(_list_gnat_ads()){
		printf("Syntaxical errors : zero\n");
		printf("Semantic errors : zero\n");
	}
	else{
		printf("program doesn't work\n");
	}
	return 0;
}
