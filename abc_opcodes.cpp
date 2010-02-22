/**************************************************************************
    Lightspark, a free flash player implementation

    Copyright (C) 2009  Alessandro Pignotti (a.pignotti@sssup.it)

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
**************************************************************************/

#include "abc.h"
#include <limits>
#include "class.h"

using namespace std;
using namespace lightspark;

uintptr_t ABCVm::bitAnd(ASObject* val2, ASObject* val1)
{
	uintptr_t i1=val1->toUInt();
	uintptr_t i2=val2->toUInt();
	val1->decRef();
	val2->decRef();
	LOG(LOG_CALLS,"bitAnd_oo " << hex << i1 << '&' << i2);
	return i1&i2;
}

uintptr_t ABCVm::increment(ASObject* o)
{
	LOG(LOG_CALLS,"increment");

	int n=o->toInt();
	o->decRef();
	return n+1;
}

uintptr_t ABCVm::bitAnd_oi(ASObject* val1, intptr_t val2)
{
	uintptr_t i1=val1->toUInt();
	uintptr_t i2=val2;
	val1->decRef();
	LOG(LOG_CALLS,"bitAnd_oi " << hex << i1 << '&' << i2);
	return i1&i2;
}

void ABCVm::setProperty(ASObject* value,ASObject* obj,multiname* name)
{
	LOG(LOG_CALLS,"setProperty " << *name << ' ' << obj);

	//We have to reset the level before finding a variable
	thisAndLevel tl=getVm()->getCurObjAndLevel();
	if(tl.cur_this==obj)
		obj->resetLevel();

	obj->setVariableByMultiname(*name,value);
	if(tl.cur_this==obj)
		obj->setLevel(tl.cur_level);

	obj->decRef();
}

void ABCVm::setProperty_i(intptr_t value,ASObject* obj,multiname* name)
{
	LOG(LOG_CALLS,"setProperty_i " << *name << ' ' <<obj);

	obj->setVariableByMultiname_i(*name,value);
	obj->decRef();
}

number_t ABCVm::convert_d(ASObject* o)
{
	LOG(LOG_CALLS, "convert_d" );
	if(o->getObjectType()!=T_UNDEFINED)
	{
		number_t ret=o->toNumber();
		o->decRef();
		return ret;
	}
	else
		return numeric_limits<double>::quiet_NaN();
}

bool ABCVm::convert_b(ASObject* o)
{
	LOG(LOG_CALLS, "convert_b" );
	bool ret=Boolean_concrete(o);
	o->decRef();
	return ret;
}

uintptr_t ABCVm::convert_u(ASObject* o)
{
	LOG(LOG_CALLS, "convert_u" );
	uintptr_t ret=o->toUInt();
	o->decRef();
	return ret;
}

intptr_t ABCVm::convert_i(ASObject* o)
{
	LOG(LOG_CALLS, "convert_i" );
	intptr_t ret=o->toInt();
	o->decRef();
	return ret;
}

void ABCVm::label()
{
	LOG(LOG_CALLS, "label" );
}

void ABCVm::lookupswitch()
{
	LOG(LOG_CALLS, "lookupswitch" );
}

ASObject* ABCVm::pushUndefined()
{
	LOG(LOG_CALLS, "pushUndefined" );
	return new Undefined;
}

ASObject* ABCVm::pushNull()
{
	LOG(LOG_CALLS, "pushNull" );
	return new Null;
}

void ABCVm::coerce_a()
{
	LOG(LOG_CALLS, "coerce_a" );
}

ASObject* ABCVm::checkfilter(ASObject* o)
{
	LOG(LOG_NOT_IMPLEMENTED, "checkfilter" );
	return o;
}

ASObject* ABCVm::coerce_s(ASObject* o)
{
	LOG(LOG_NOT_IMPLEMENTED, "coerce_s" );
	return o;
}

void ABCVm::coerce(call_context* th, int n)
{
	multiname* name=th->context->getMultiname(n,NULL); 
	LOG(LOG_CALLS,"coerce " << *name);
}

void ABCVm::pop()
{
	LOG(LOG_CALLS, "pop: DONE" );
}

void ABCVm::getLocal_int(int n, int v)
{
	LOG(LOG_CALLS,"getLocal[" << n << "] (int)= " << dec << v);
}

void ABCVm::getLocal(ASObject* o, int n)
{
	LOG(LOG_CALLS,"getLocal[" << n << "] (" << o << ") " << o->toString(true));
}

void ABCVm::getLocal_short(int n)
{
	LOG(LOG_CALLS,"getLocal[" << n << "]");
}

void ABCVm::setLocal(int n)
{
	LOG(LOG_CALLS,"setLocal[" << n << "]");
}

void ABCVm::setLocal_int(int n, int v)
{
	LOG(LOG_CALLS,"setLocal[" << n << "] (int)= " << dec << v);
}

void ABCVm::setLocal_obj(int n, ASObject* v)
{
	LOG(LOG_CALLS,"setLocal[" << n << "] = " << v->toString(true));
}

intptr_t ABCVm::pushShort(intptr_t n)
{
	LOG(LOG_CALLS, "pushShort " << n );
	return n;
}

void ABCVm::setSlot(ASObject* value, ASObject* obj, int n)
{
	LOG(LOG_CALLS,"setSlot " << dec << n);
	obj->setSlot(n,value);
	obj->decRef();
}

ASObject* ABCVm::getSlot(ASObject* obj, int n)
{
	LOG(LOG_CALLS,"getSlot " << dec << n);
	ASObject* ret=obj->getSlot(n);
	ret->incRef();
	obj->decRef();
	return ret;
}

ASObject* ABCVm::negate(ASObject* v)
{
	LOG(LOG_CALLS, "negate" );
	ASObject* ret=new Number(-(v->toNumber()));
	v->decRef();
	return ret;
}

uintptr_t ABCVm::bitNot(ASObject* val)
{
	uintptr_t i1=val->toUInt();
	val->decRef();
	LOG(LOG_CALLS,"bitNot " << hex << i1);
	return ~i1;
}

uintptr_t ABCVm::bitXor(ASObject* val2, ASObject* val1)
{
	int i1=val1->toUInt();
	int i2=val2->toUInt();
	val1->decRef();
	val2->decRef();
	LOG(LOG_CALLS,"bitXor " << hex << i1 << '^' << i2);
	return i1^i2;
}

uintptr_t ABCVm::bitOr_oi(ASObject* val2, uintptr_t val1)
{
	int i1=val1;
	int i2=val2->toUInt();
	val2->decRef();
	LOG(LOG_CALLS,"bitOr " << hex << i1 << '|' << i2);
	return i1|i2;
}

uintptr_t ABCVm::bitOr(ASObject* val2, ASObject* val1)
{
	int i1=val1->toUInt();
	int i2=val2->toUInt();
	val1->decRef();
	val2->decRef();
	LOG(LOG_CALLS,"bitOr " << hex << i1 << '|' << i2);
	return i1|i2;
}

void ABCVm::callProperty(call_context* th, int n, int m)
{
	ASObject** args=new ASObject*[m];
	for(int i=0;i<m;i++)
		args[m-i-1]=th->runtime_stack_pop();

	multiname* name=th->context->getMultiname(n,th);
	LOG(LOG_CALLS,"callProperty " << *name << ' ' << m);

	ASObject* obj=th->runtime_stack_pop();
	if(obj->prototype)
		LOG(LOG_CALLS,obj->prototype->class_name);

	//We have to reset the level, as we may be getting a function defined at a lower level
	thisAndLevel tl=getVm()->getCurObjAndLevel();
	if(tl.cur_this==obj)
		obj->resetLevel();

	//We should skip the special implementation of get
	objAndLevel o=obj->getVariableByMultiname(*name, true);

	if(tl.cur_this==obj)
		obj->setLevel(tl.cur_level);

	if(o.obj)
	{
		//Run the deferred initialization if needed
		if(o.obj->getObjectType()==T_DEFINABLE)
		{
			LOG(LOG_CALLS,"We got a function not yet valid");
			Definable* d=static_cast<Definable*>(o.obj);
			d->define(obj);
			assert(obj==getGlobal());
			o=obj->getVariableByMultiname(*name);
		}

		//If o is already a function call it
		if(o.obj->getObjectType()==T_FUNCTION)
		{
			IFunction* f=static_cast<IFunction*>(o.obj);
			//Methods has to be runned with their own class this
			//The owner has to be increffed
			obj->incRef();
			ASObject* ret=NULL;
			//HACK for Proxy, here till callProperty proxying is implemented
			if(name->ns.size()==1 && name->ns[0].name==flash_proxy)
			{
				Proxy* p=dynamic_cast<Proxy*>(obj->implementation);
				assert(p);
				p->suppress=true;
				ret=f->fast_call(obj,args,m,o.level);
				p->suppress=false;
			}
			else
				ret=f->fast_call(obj,args,m,o.level);
			th->runtime_stack_push(ret);
		}
		else if(o.obj->getObjectType()==T_UNDEFINED)
		{
			LOG(LOG_NOT_IMPLEMENTED,"We got a Undefined function on obj " << ((obj->prototype)?obj->prototype->class_name:"Object"));
			th->runtime_stack_push(new Undefined);
		}
		else
		{
			if(m==1) //Assume this is a constructor
			{
				LOG(LOG_CALLS,"Passthorugh of " << args[0]);
				args[0]->incRef();
				th->runtime_stack_push(args[0]);
			}
			else
				abort();

			/*
			IFunction* f=static_cast<IFunction*>(o->getVariableByQName("Call","",owner));
			if(f)
			{
				ASObject* ret=f->fast_call(o,args,m);
				th->runtime_stack_push(ret);
			}
			else
			{
				LOG(LOG_NOT_IMPLEMENTED,"No such function, returning Undefined");
				th->runtime_stack_push(new Undefined);
			}*/
		}
	}
	else
	{
		LOG(LOG_NOT_IMPLEMENTED,"Calling an undefined function " << *name << " on obj " << 
				((obj->prototype)?obj->prototype->class_name:"Object"));
		th->runtime_stack_push(new Undefined);
	}
	LOG(LOG_CALLS,"End of calling " << *name);

	obj->decRef();
	delete[] args;
}

intptr_t ABCVm::getProperty_i(ASObject* obj, multiname* name)
{
	LOG(LOG_CALLS, "getProperty_i " << *name );

	//TODO: implement exception handling to find out if no integer can be returned
	intptr_t ret=obj->getVariableByMultiname_i(*name);

	obj->decRef();
	return ret;
}

ASObject* ABCVm::getProperty(ASObject* obj, multiname* name)
{
	LOG(LOG_CALLS, "getProperty " << *name << ' ' << obj);

	int v=getVm()->method_this_stack.size();

	//We have to reset the level before finding a variable
	thisAndLevel tl=getVm()->getCurObjAndLevel();
	if(tl.cur_this==obj)
		obj->resetLevel();

	objAndLevel ret=obj->getVariableByMultiname(*name);

	if(tl.cur_this==obj)
		obj->setLevel(tl.cur_level);
	
	assert(v==getVm()->method_this_stack.size());

	if(ret.obj==NULL)
	{
		if(obj->prototype)
		{
			LOG(LOG_NOT_IMPLEMENTED,"Property not found " << *name << " on type " << obj->prototype->class_name);
		}
		else
		{
			LOG(LOG_NOT_IMPLEMENTED,"Property not found " << *name);
		}
		return new Undefined;
	}
	else
	{
		//If we are getting a function object attach the the current scope
		if(ret.obj->getObjectType()==T_FUNCTION)
		{
			//TODO: maybe also the level should be binded
			LOG(LOG_CALLS,"Attaching this to function " << name);
			IFunction* f=static_cast<IFunction*>(ret.obj)->bind(obj,ret.level);
			obj->decRef();
			//No incref is needed, as the function is a new instance
			return f;
		}
		else if(ret.obj->getObjectType()==T_DEFINABLE)
		{
			//LOG(ERROR,"Property " << name << " is not yet valid");
			abort();
			/*Definable* d=static_cast<Definable*>(ret.obj);
			d->define(obj);
			ret=obj->getVariableByMultiname(*name,owner);
			ret->incRef();*/
		}
	}
	ret.obj->incRef();
	obj->decRef();
	return ret.obj;
}

number_t ABCVm::divide(ASObject* val2, ASObject* val1)
{
	if(val1->getObjectType()==T_UNDEFINED ||
		val2->getObjectType()==T_UNDEFINED)
	{
		//HACK
		LOG(LOG_NOT_IMPLEMENTED,"subtract: HACK");
		return 0;
	}
	double num1=val1->toNumber();
	double num2=val2->toNumber();

	val1->decRef();
	val2->decRef();
	LOG(LOG_CALLS,"divide "  << num1 << '/' << num2);
	return num1/num2;
}

void ABCVm::pushWith(call_context* th)
{
	ASObject* t=th->runtime_stack_pop();
	LOG(LOG_CALLS, "pushWith " << t );
	th->scope_stack.push_back(t);
}

void ABCVm::pushScope(call_context* th)
{
	ASObject* t=th->runtime_stack_pop();
	LOG(LOG_CALLS, "pushScope " << t );
	th->scope_stack.push_back(t);
}

ASObject* ABCVm::getGlobalScope()
{
	ASObject* ret=getGlobal();
	LOG(LOG_CALLS,"getGlobalScope: " << ret);
	ret->incRef();
	return ret;
}

uintptr_t ABCVm::decrement(ASObject* o)
{
	LOG(LOG_CALLS,"decrement");

	int n=o->toInt();
	o->decRef();
	return n-1;
}

uintptr_t ABCVm::decrement_i(ASObject* o)
{
	LOG(LOG_CALLS,"decrement_i");

	int n=o->toInt();
	o->decRef();
	return n-1;
}

bool ABCVm::ifNLT(ASObject* obj2, ASObject* obj1)
{
	//Real comparision demanded to object
	bool ret=!(obj1->isLess(obj2));
	LOG(LOG_CALLS,"ifNLT (" << ((ret)?"taken)":"not taken)"));

	obj2->decRef();
	obj1->decRef();
	return ret;
}

bool ABCVm::ifLT(ASObject* obj2, ASObject* obj1)
{
	//Real comparision demanded to object
	bool ret=obj1->isLess(obj2);
	LOG(LOG_CALLS,"ifLT (" << ((ret)?"taken)":"not taken)"));

	obj2->decRef();
	obj1->decRef();
	return ret;
}

bool ABCVm::ifLT_oi(ASObject* obj2, intptr_t val1)
{
	LOG(LOG_CALLS,"ifLT_oi");

	//As ECMA said, on NaN return undefined... and undefined means not jump
	bool ret;
	if(obj2->getObjectType()==T_UNDEFINED)
		ret=false;
	else
		ret=val1<obj2->toInt();

	obj2->decRef();
	return ret;
}

bool ABCVm::ifLT_io(intptr_t val2, ASObject* obj1)
{
	LOG(LOG_CALLS,"ifLT_io ");

	bool ret=obj1->toInt()<val2;

	obj1->decRef();
	return ret;
}

bool ABCVm::ifNE(ASObject* obj1, ASObject* obj2)
{
	//Real comparision demanded to object
	bool ret=!(obj1->isEqual(obj2));
	LOG(LOG_CALLS,"ifNE (" << ((ret)?"taken)":"not taken)"));

	obj2->decRef();
	obj1->decRef();
	return ret;
}

bool ABCVm::ifNE_oi(ASObject* obj1, intptr_t val2)
{
	//HACK
	if(obj1->getObjectType()==T_UNDEFINED)
		return false;
	bool ret=obj1->toInt()!=val2;
	LOG(LOG_CALLS,"ifNE (" << ((ret)?"taken)":"not taken)"));

	obj1->decRef();
	return ret;
}

intptr_t ABCVm::pushByte(intptr_t n)
{
	LOG(LOG_CALLS, "pushByte " << n );
	return n;
}

number_t ABCVm::multiply_oi(ASObject* val2, intptr_t val1)
{
	double num1=val1;
	double num2=val2->toNumber();
	val2->decRef();
	LOG(LOG_CALLS,"multiply_oi "  << num1 << '*' << num2);
	return num1*num2;
}

number_t ABCVm::multiply(ASObject* val2, ASObject* val1)
{
	double num1=val1->toNumber();
	double num2=val2->toNumber();
	val1->decRef();
	val2->decRef();
	LOG(LOG_CALLS,"multiply "  << num1 << '*' << num2);
	return num1*num2;
}

void ABCVm::incLocal_i(call_context* th, int n)
{
	LOG(LOG_CALLS, "incLocal_i " << n );
	if(th->locals[n]->getObjectType()==T_INTEGER)
	{
		Integer* i=static_cast<Integer*>(th->locals[n]);
		i->val++;
	}
	else
	{
		LOG(LOG_NOT_IMPLEMENTED,"Cannot increment type " << th->locals[n]->getObjectType());
	}

}

void ABCVm::construct(call_context* th, int m)
{
	LOG(LOG_CALLS, "construct " << m);
	arguments args(m);
	for(int i=0;i<m;i++)
		args.set(m-i-1,th->runtime_stack_pop());

	ASObject* obj=th->runtime_stack_pop();

	if(obj->getObjectType()==T_DEFINABLE)
	{
		LOG(LOG_ERROR,"Check");
		abort();
	/*	LOG(LOG_CALLS,"Deferred definition of property " << name);
		Definable* d=static_cast<Definable*>(o);
		d->define(obj);
		o=obj->getVariableByMultiname(name,owner);
		LOG(LOG_CALLS,"End of deferred definition of property " << name);*/
	}

	LOG(LOG_CALLS,"Constructing");

	ASObject* ret;
	if(obj->getObjectType()==T_CLASS)
	{
		Class_base* o_class=static_cast<Class_base*>(obj);
		ret=o_class->getInstance(true,&args)->obj;
	}
	else if(obj->getObjectType()==T_FUNCTION)
	{
		SyntheticFunction* sf=dynamic_cast<SyntheticFunction*>(obj);
		assert(sf);
		ret=new ASObject;
		if(sf->mi->body)
		{
			LOG(LOG_CALLS,"Building method traits");
			for(int i=0;i<sf->mi->body->trait_count;i++)
				th->context->buildTrait(ret,&sf->mi->body->traits[i],false);
			ret->incRef();
			assert(sf->closure_this==NULL);
			sf->call(ret,&args,0);

			//Let's see if an AS prototype has been defined on the function
			ASObject* asp=sf->getVariableByQName("prototype","").obj;
			if(asp)
				asp->incRef();

			//Now add our prototype
			sf->incRef();
			ret->prototype=new Class_function(sf,asp);
		}
	}
	else
		abort();

	obj->decRef();
	LOG(LOG_CALLS,"End of constructing " << ret);
	th->runtime_stack_push(ret);
}

void ABCVm::constructGenericType(call_context* th, int m)
{
	abort();
	LOG(LOG_CALLS, "constructGenericType " << m);
	arguments args(m);
	for(int i=0;i<m;i++)
		args.set(m-i-1,th->runtime_stack_pop());
	__asm__("int $3");

	ASObject* obj=th->runtime_stack_pop();

	if(obj->getObjectType()==T_DEFINABLE)
	{
		LOG(LOG_ERROR,"Check");
		abort();
	/*	LOG(LOG_CALLS,"Deferred definition of property " << name);
		Definable* d=static_cast<Definable*>(o);
		d->define(obj);
		o=obj->getVariableByMultiname(name,owner);
		LOG(LOG_CALLS,"End of deferred definition of property " << name);*/
	}

	LOG(LOG_CALLS,"Constructing");
	Class_base* o_class=static_cast<Class_base*>(obj);
	assert(o_class->getObjectType()==T_CLASS);
	ASObject* ret=o_class->getInstance(true,&args)->obj;

//	args.decRef();
	obj->decRef();
	LOG(LOG_CALLS,"End of constructing");
	th->runtime_stack_push(ret);
}

ASObject* ABCVm::typeOf(ASObject* obj)
{
	LOG(LOG_CALLS,"typeOf");
	string ret;
	switch(obj->getObjectType())
	{
		case T_UNDEFINED:
			ret="undefined";
			break;
		case T_OBJECT:
		case T_NULL:
		case T_ARRAY:
			ret="object";
			break;
		case T_BOOLEAN:
			ret="boolean";
			break;
		case T_NUMBER:
		case T_INTEGER:
			ret="number";
			break;
		case T_STRING:
			ret="string";
			break;
		case T_FUNCTION:
			ret="function";
			break;
		default:
			return new Undefined;
	}
	obj->decRef();
	return Class<ASString>::getInstanceS(true,ret)->obj;
}

void ABCVm::callPropVoid(call_context* th, int n, int m)
{
	multiname* name=th->context->getMultiname(n,th); 
	LOG(LOG_CALLS,"callPropVoid " << *name << ' ' << m);

	arguments args(m);
	for(int i=0;i<m;i++)
		args.set(m-i-1,th->runtime_stack_pop());
	ASObject* obj=th->runtime_stack_pop();

	if(obj->prototype)
		LOG(LOG_CALLS, obj->prototype->class_name);

	//We have to reset the level, as we may be getting a function defined at a lower level
	thisAndLevel tl=getVm()->getCurObjAndLevel();
	if(tl.cur_this==obj)
		obj->resetLevel();

	//We should skip the special implementation of get
	objAndLevel o=obj->getVariableByMultiname(*name,true);

	if(tl.cur_this==obj)
		obj->setLevel(tl.cur_level);

	if(o.obj)
	{
		//If o is already a function call it, otherwise find the Call method
		if(o.obj->getObjectType()==T_FUNCTION)
		{
			IFunction* f=static_cast<IFunction*>(o.obj)->getOverride();
			obj->incRef();

			//HACK for Proxy, here till callProperty proxying is implemented
			if(name->ns.size()==1 && name->ns[0].name==flash_proxy)
			{
				Proxy* p=dynamic_cast<Proxy*>(obj->implementation);
				assert(p);
				p->suppress=true;
				f->call(obj,&args,o.level);
				p->suppress=false;
			}
			else
				f->call(obj,&args,o.level);
		}
		else if(o.obj->getObjectType()==T_UNDEFINED)
		{
			LOG(LOG_NOT_IMPLEMENTED,"Calling an undefined function " << *name << " on obj " << 
					((obj->prototype)?obj->prototype->class_name:"Object"));
		}
		else if(o.obj->getObjectType()==T_DEFINABLE)
		{
			LOG(LOG_NOT_IMPLEMENTED,"We got a function not yet valid");
		}
		else
		{
			abort();
/*			IFunction* f=static_cast<IFunction*>(o->getVariableByQName(".Call","",owner));
			f->call(owner,&args);*/
		}
	}
	else
	{
		if(obj->prototype)
		{
			LOG(LOG_NOT_IMPLEMENTED,"We got a Undefined function " << name->name_s << " on obj type " << obj->prototype->class_name);
		}
		else
		{
			LOG(LOG_NOT_IMPLEMENTED,"We got a Undefined function " << name->name_s);
		}
	}

	obj->decRef();
	LOG(LOG_CALLS,"End of calling " << *name);
}

void ABCVm::jump(call_context* th, int offset)
{
	LOG(LOG_CALLS,"jump " << offset);
}

bool ABCVm::ifTrue(ASObject* obj1)
{
	bool ret=Boolean_concrete(obj1);
	LOG(LOG_CALLS,"ifTrue (" << ((ret)?"taken)":"not taken)"));

	obj1->decRef();
	return ret;
}

intptr_t ABCVm::modulo(ASObject* val1, ASObject* val2)
{
	int num2=val2->toInt();
	int num1=val1->toInt();

	val1->decRef();
	val2->decRef();
	LOG(LOG_CALLS,"modulo "  << num1 << '%' << num2);
	return num1%num2;
}

number_t ABCVm::subtract_oi(ASObject* val2, intptr_t val1)
{
	int num2=val2->toInt();
	int num1=val1;

	val2->decRef();
	LOG(LOG_CALLS,"subtract_oi " << num1 << '-' << num2);
	return num1-num2;
}

number_t ABCVm::subtract_do(number_t val2, ASObject* val1)
{
	assert(val1->getObjectType()!=T_UNDEFINED);
	number_t num2=val2;
	number_t num1=val1->toNumber();

	val1->decRef();
	LOG(LOG_CALLS,"subtract_do " << num1 << '-' << num2);
	return num1-num2;
}

number_t ABCVm::subtract_io(intptr_t val2, ASObject* val1)
{
	if(val1->getObjectType()==T_UNDEFINED)
	{
		//HACK
		LOG(LOG_NOT_IMPLEMENTED,"subtract: HACK");
		return 0;
	}
	int num2=val2;
	int num1=val1->toInt();

	val1->decRef();
	LOG(LOG_CALLS,"subtract_io " << dec << num1 << '-' << num2);
	return num1-num2;
}

number_t ABCVm::subtract(ASObject* val2, ASObject* val1)
{
	if(val1->getObjectType()==T_UNDEFINED ||
		val2->getObjectType()==T_UNDEFINED)
	{
		//HACK
		LOG(LOG_NOT_IMPLEMENTED,"subtract: HACK");
		return 0;
	}
	int num2=val2->toInt();
	int num1=val1->toInt();

	val1->decRef();
	val2->decRef();
	LOG(LOG_CALLS,"subtract " << num1 << '-' << num2);
	return num1-num2;
}

void ABCVm::pushUInt(call_context* th, int n)
{
	u32 i=th->context->constant_pool.uinteger[n];
	LOG(LOG_CALLS, "pushUInt [" << dec << n << "] " << i);
}

void ABCVm::pushInt(call_context* th, int n)
{
	s32 i=th->context->constant_pool.integer[n];
	LOG(LOG_CALLS, "pushInt [" << dec << n << "] " << i);
}

void ABCVm::pushDouble(call_context* th, int n)
{
	d64 d=th->context->constant_pool.doubles[n];
	LOG(LOG_CALLS, "pushDouble [" << dec << n << "] " << d);
}

void ABCVm::kill(call_context* th, int n)
{
	LOG(LOG_CALLS, "kill " << n );
}

ASObject* ABCVm::add(ASObject* val2, ASObject* val1)
{
	//Implement ECMA add algorithm, for XML and default
	if(val1->getObjectType()==T_INTEGER && val2->getObjectType()==T_INTEGER)
	{
		intptr_t num2=val2->toInt();
		intptr_t num1=val1->toInt();
		LOG(LOG_CALLS,"add " << num1 << '+' << num2);
		val1->decRef();
		val2->decRef();
		return abstract_i(num1+num2);
	}
	else if(val1->getObjectType()==T_ARRAY)
	{
		//Array concatenation
		Array* ar=static_cast<Array*>(val1->implementation);
		ar->push(val2);
		return val1;
	}
	else if(val1->getObjectType()==T_STRING || val2->getObjectType()==T_STRING)
	{
		string a(val1->toString().raw_buf());
		string b(val2->toString().raw_buf());
		LOG(LOG_CALLS,"add " << a << '+' << b);
		val1->decRef();
		val2->decRef();
		return Class<ASString>::getInstanceS(true,a+b)->obj;
	}
	else if(val1->getObjectType()==T_NUMBER || val2->getObjectType()==T_NUMBER)
	{
		double num2=val2->toNumber();
		double num1=val1->toNumber();
		LOG(LOG_CALLS,"add " << num1 << '+' << num2);
		val1->decRef();
		val2->decRef();
		return abstract_d(num1+num2);
	}
	else
	{
		LOG(LOG_NOT_IMPLEMENTED,"Add between types " << val1->getObjectType() << ' ' << val2->getObjectType());
		return new Undefined;
	}

}

ASObject* ABCVm::add_oi(ASObject* val2, intptr_t val1)
{
	//Implement ECMA add algorithm, for XML and default
	if(val2->getObjectType()==T_INTEGER)
	{
		Integer* ip=static_cast<Integer*>(val2);
		intptr_t num2=ip->val;
		intptr_t num1=val1;
		val2->decRef();
		LOG(LOG_CALLS,"add " << num1 << '+' << num2);
		return abstract_i(num1+num2);
	}
	else if(val2->getObjectType()==T_NUMBER)
	{
		double num2=val2->toNumber();
		double num1=val1;
		val2->decRef();
		LOG(LOG_CALLS,"add " << num1 << '+' << num2);
		return abstract_d(num1+num2);
	}
	else if(val2->getObjectType()==T_STRING)
	{
		tiny_string a(val1);
		const tiny_string& b=val2->toString();
		val2->decRef();
		LOG(LOG_CALLS,"add " << a << '+' << b);
		return Class<ASString>::getInstanceS(true,a+b)->obj;
	}
	else if(val2->getObjectType()==T_ARRAY)
	{
		abort();
		/*//Array concatenation
		ASArray* ar=static_cast<ASArray*>(val1);
		ar->push(val2);
		return ar;*/
	}
	else
	{
		LOG(LOG_NOT_IMPLEMENTED,"Add between integer and " << val2->getObjectType());
		return new Undefined;
	}

}

ASObject* ABCVm::add_od(ASObject* val2, number_t val1)
{
	//Implement ECMA add algorithm, for XML and default
	if(val2->getObjectType()==T_NUMBER)
	{
		double num2=val2->toNumber();
		double num1=val1;
		val2->decRef();
		LOG(LOG_CALLS,"add " << num1 << '+' << num2);
		return abstract_d(num1+num2);
	}
	else if(val2->getObjectType()==T_INTEGER)
	{
		double num2=val2->toNumber();
		double num1=val1;
		val2->decRef();
		LOG(LOG_CALLS,"add " << num1 << '+' << num2);
		return abstract_d(num1+num2);
	}
	else if(val2->getObjectType()==T_STRING)
	{
		tiny_string a(val1);
		const tiny_string& b=val2->toString();
		val2->decRef();
		LOG(LOG_CALLS,"add " << a << '+' << b);
		return Class<ASString>::getInstanceS(true,a+b)->obj;
	}
	else if(val2->getObjectType()==T_ARRAY)
	{
		abort();
		/*//Array concatenation
		ASArray* ar=static_cast<ASArray*>(val1);
		ar->push(val2);
		return ar;*/
	}
	else
	{
		LOG(LOG_NOT_IMPLEMENTED,"Add between types number and " << val2->getObjectType());
		return new Undefined;
	}

}

uintptr_t ABCVm::lShift(ASObject* val1, ASObject* val2)
{
	uint32_t i2=val2->toInt();
	int32_t i1=val1->toInt()&0x1f;
	val1->decRef();
	val2->decRef();
	LOG(LOG_CALLS,"lShift "<<hex<<i2<<"<<"<<i1<<dec);
	//Left shift are supposed to always work in 32bit
	uint32_t ret=i2<<i1;
	return ret;
}

uintptr_t ABCVm::lShift_io(uintptr_t val1, ASObject* val2)
{
	uint32_t i2=val2->toInt();
	int32_t i1=val1&0x1f;
	val2->decRef();
	LOG(LOG_CALLS,"lShift "<<hex<<i2<<"<<"<<i1<<dec);
	//Left shift are supposed to always work in 32bit
	uint32_t ret=i2<<i1;
	return ret;
}

uintptr_t ABCVm::rShift(ASObject* val1, ASObject* val2)
{
	int32_t i2=val2->toInt();
	int32_t i1=val1->toInt()&0x1f;
	val1->decRef();
	val2->decRef();
	LOG(LOG_CALLS,"rShift "<<hex<<i2<<">>"<<i1<<dec);
	return i2>>i1;
}

uintptr_t ABCVm::urShift(ASObject* val1, ASObject* val2)
{
	uint32_t i2=val2->toInt();
	int32_t i1=val1->toInt()&0x1f;
	val1->decRef();
	val2->decRef();
	LOG(LOG_CALLS,"urShift "<<hex<<i2<<">>"<<i1<<dec);
	return i2>>i1;
}

uintptr_t ABCVm::urShift_io(uintptr_t val1, ASObject* val2)
{
	uint32_t i2=val2->toInt();
	int32_t i1=val1&0x1f;
	val2->decRef();
	LOG(LOG_CALLS,"urShift "<<hex<<i2<<">>"<<i1<<dec);
	return i2>>i1;
}

bool ABCVm::_not(ASObject* v)
{
	LOG(LOG_CALLS, "not" );
	bool ret=!Boolean_concrete(v);
	v->decRef();
	return ret;
}

bool ABCVm::equals(ASObject* val2, ASObject* val1)
{
	bool ret=val1->isEqual(val2);
	LOG(LOG_CALLS, "equals " << ret);
	val1->decRef();
	val2->decRef();
	return ret;
}

bool ABCVm::strictEquals(ASObject* obj2, ASObject* obj1)
{
	LOG(LOG_CALLS, "strictEquals" );
	if(obj1->getObjectType()!=obj2->getObjectType())
		return false;
	return equals(obj2,obj1);
}

void ABCVm::dup()
{
	LOG(LOG_CALLS, "dup: DONE" );
}

bool ABCVm::pushTrue()
{
	LOG(LOG_CALLS, "pushTrue" );
	return true;
}

bool ABCVm::pushFalse()
{
	LOG(LOG_CALLS, "pushFalse" );
	return false;
}

ASObject* ABCVm::pushNaN()
{
	LOG(LOG_CALLS, "pushNaN" );
	//Not completely correct, but mostly ok
	return new Undefined;
}

bool ABCVm::ifGT(ASObject* obj2, ASObject* obj1)
{
	LOG(LOG_CALLS,"ifGT");

	//Real comparision demanded to object
	bool ret=obj1->isGreater(obj2);

	obj2->decRef();
	obj1->decRef();
	return ret;
}

bool ABCVm::ifNGT(ASObject* obj2, ASObject* obj1)
{

	//Real comparision demanded to object
	bool ret= !(obj1->isGreater(obj2));
	LOG(LOG_CALLS,"ifNGT (" << ((ret)?"taken)":"not taken)"));

	obj2->decRef();
	obj1->decRef();
	return ret;
}

bool ABCVm::ifLE(ASObject* obj2, ASObject* obj1)
{
	LOG(LOG_CALLS,"ifLE");

	//Real comparision demanded to object
	bool ret=obj1->isLess(obj2) || obj1->isEqual(obj2);
	obj1->decRef();
	obj2->decRef();
	return ret;
}

bool ABCVm::ifNLE(ASObject* obj2, ASObject* obj1)
{
	LOG(LOG_CALLS,"ifNLE");

	//Real comparision demanded to object
	bool ret=!(obj1->isLess(obj2) || obj1->isEqual(obj2));
	obj1->decRef();
	obj2->decRef();
	return ret;
}

bool ABCVm::ifGE(ASObject* obj2, ASObject* obj1)
{
	LOG(LOG_CALLS,"ifGE");
	//Real comparision demanded to object
	bool ret=obj1->isGreater(obj2) || obj1->isEqual(obj2);
	obj1->decRef();
	obj2->decRef();
	return ret;
}

bool ABCVm::ifNGE(ASObject* obj2, ASObject* obj1)
{
	LOG(LOG_CALLS,"ifNGE");

	//Real comparision demanded to object
	bool ret=!(obj1->isGreater(obj2) || obj1->isEqual(obj2));
	obj1->decRef();
	obj2->decRef();
	return ret;
}

void ABCVm::_throw(call_context* th)
{
	LOG(LOG_NOT_IMPLEMENTED, "throw" );
	abort();
}

void ABCVm::setSuper(call_context* th, int n)
{
	ASObject* value=th->runtime_stack_pop();
	multiname* name=th->context->getMultiname(n,th); 
	LOG(LOG_CALLS,"setSuper " << *name);

	ASObject* obj=th->runtime_stack_pop();
	assert(obj->actualPrototype);
	//Store the old prototype
	Class_base* old_prototype=obj->actualPrototype;

	//Move the object prototype
	obj->actualPrototype=old_prototype->super;

	//We modify the cur_level of obj
	obj->decLevel();

	obj->setVariableByMultiname(*name,value, false);

	//And the reset it using the stack
	thisAndLevel tl=getVm()->getCurObjAndLevel();
	//What if using [sg]etSuper not on this??
	assert(tl.cur_this==obj);
	tl.cur_this->setLevel(tl.cur_level);

	//Reset prototype to its previous value
	assert(obj->actualPrototype==old_prototype->super);
	obj->actualPrototype=old_prototype;

	obj->decRef();
}

void ABCVm::getSuper(call_context* th, int n)
{
	multiname* name=th->context->getMultiname(n,th); 
	LOG(LOG_CALLS,"getSuper " << *name);

	ASObject* obj=th->runtime_stack_pop();
	assert(obj->actualPrototype);
	//Store the old prototype
	Class_base* old_prototype=obj->actualPrototype;

	//Move the object protoype and level up
	obj->actualPrototype=old_prototype->super;

	thisAndLevel tl=getVm()->getCurObjAndLevel();
	//What if using [sg]etSuper not on this??
	assert(tl.cur_this==obj);

	//We modify the cur_level of obj
	obj->decLevel();

	//Should we skip implementation? I think it's reasonable
	ASObject* o=obj->getVariableByMultiname(*name, true, false).obj;

	tl=getVm()->getCurObjAndLevel();
	//What if using [sg]etSuper not on this??
	assert(tl.cur_this==obj);
	//And the reset it using the stack
	tl.cur_this->setLevel(tl.cur_level);

	if(o)
	{
		if(o->getObjectType()==T_DEFINABLE)
		{
			LOG(LOG_CALLS,"We got an object not yet valid");
			Definable* d=static_cast<Definable*>(o);
			d->define(obj);
			assert(obj==getGlobal());
			o=obj->getVariableByMultiname(*name).obj;
		}
		o->incRef();
		th->runtime_stack_push(o);
	}
	else
	{
		LOG(LOG_NOT_IMPLEMENTED,"NOT found " << name->name_s<< ", pushing Undefined");
		th->runtime_stack_push(new Undefined);
	}

	//Reset prototype to its previous value
	assert(obj->actualPrototype==old_prototype->super);
	obj->actualPrototype=old_prototype;

	obj->decRef();
}

void ABCVm::getLex(call_context* th, int n)
{
	multiname* name=th->context->getMultiname(n,th);
	LOG(LOG_CALLS, "getLex: " << *name );
	vector<ASObject*>::reverse_iterator it=th->scope_stack.rbegin();
	ASObject* o;

	//Find out the current 'this', when looking up over it, we have to consider all of it
	thisAndLevel tl=getVm()->getCurObjAndLevel();
	for(it;it!=th->scope_stack.rend();it++)
	{
		if(*it==tl.cur_this)
			tl.cur_this->resetLevel();

		objAndLevel tmpo=(*it)->getVariableByMultiname(*name);
		if(*it==tl.cur_this)
			tl.cur_this->setLevel(tl.cur_level);

		o=tmpo.obj;
		if(o)
		{
			//If we are getting a function object attach the the current scope
			if(o->getObjectType()==T_FUNCTION)
			{
				LOG(LOG_CALLS,"Attaching this to function " << name);
				IFunction* f=static_cast<IFunction*>(o)->bind(*it,tmpo.level);
				o=f;
			}
			else if(o->getObjectType()==T_DEFINABLE)
			{
				LOG(LOG_CALLS,"Deferred definition of property " << *name);
				Definable* d=static_cast<Definable*>(o);
				d->define(*it);
				assert(*it==getGlobal());
				o=(*it)->getVariableByMultiname(*name).obj;
				LOG(LOG_CALLS,"End of deferred definition of property " << *name);
			}
			th->runtime_stack_push(o);
			o->incRef();
			return;
		}
	}
	if(o==NULL)
	{
		LOG(LOG_CALLS, "NOT found, trying Global" );
		o=getGlobal()->getVariableByMultiname(*name).obj;
		if(o)
		{
			if(o->getObjectType()==T_DEFINABLE)
			{
				LOG(LOG_CALLS,"Deferred definition of property " << *name);
				Definable* d=static_cast<Definable*>(o);
				d->define(getGlobal());
				o=getGlobal()->getVariableByMultiname(*name).obj;
				LOG(LOG_CALLS,"End of deferred definition of property " << *name);
			}
			else if(o->getObjectType()==T_FUNCTION)
				abort();

			th->runtime_stack_push(o);
			o->incRef();
		}
		else
		{
			LOG(LOG_NOT_IMPLEMENTED,"NOT found " << name->name_s<< ", pushing Undefined");
			th->runtime_stack_push(new Undefined);
		}
	}
}

void ABCVm::constructSuper(call_context* th, int n)
{
	LOG(LOG_CALLS, "constructSuper " << n);
	arguments args(n);
	for(int i=0;i<n;i++)
		args.set(n-i-1,th->runtime_stack_pop());

	ASObject* obj=th->runtime_stack_pop();

	if(obj->actualPrototype==NULL)
	{
		LOG(LOG_CALLS,"No prototype. Returning");
		abort();
		return;
	}

	//Store the old prototype
	Class_base* old_prototype=obj->actualPrototype;
	LOG(LOG_CALLS,"Cur prototype name " << obj->actualPrototype->class_name);
	//Move the object protoype and level up
	obj->actualPrototype=old_prototype->super;
	LOG(LOG_CALLS,"Super prototype name " << obj->actualPrototype->class_name);
	assert(obj->actualPrototype);

	thisAndLevel tl=getVm()->getCurObjAndLevel();
	assert(tl.cur_this==obj);
	assert(tl.cur_level==obj->getLevel());
	int level=obj->getLevel();
	obj->decLevel();
	//Check that current 'this' is the object
	obj->handleConstruction(&args, false);
	LOG(LOG_CALLS,"End super construct ");
	obj->setLevel(level);

	//Reset prototype to its previous value
	assert(obj->actualPrototype==old_prototype->super);
	obj->actualPrototype=old_prototype;

	obj->decRef();
}

ASObject* ABCVm::findProperty(call_context* th, int n)
{
	multiname* name=th->context->getMultiname(n,th);
	LOG(LOG_CALLS, "findProperty " << *name );

	vector<ASObject*>::reverse_iterator it=th->scope_stack.rbegin();
	objAndLevel o(NULL,0);
	ASObject* ret=NULL;
	thisAndLevel tl=getVm()->getCurObjAndLevel();
	for(it;it!=th->scope_stack.rend();it++)
	{
		if(*it==tl.cur_this)
			tl.cur_this->resetLevel();

		o=(*it)->getVariableByMultiname(*name);
		if(*it==tl.cur_this)
			tl.cur_this->setLevel(tl.cur_level);

		if(o.obj)
		{
			//We have to return the object, not the property
			ret=*it;
			break;
		}
	}
	if(o.obj==NULL)
	{
		LOG(LOG_CALLS, "NOT found, pushing global" );
		ret=getGlobal();
	}

	assert(ret);
	ret->incRef();
	return ret;
}

ASObject* ABCVm::findPropStrict(call_context* th, int n)
{
	multiname* name=th->context->getMultiname(n,th);
	LOG(LOG_CALLS, "findPropStrict " << *name );

	vector<ASObject*>::reverse_iterator it=th->scope_stack.rbegin();
	objAndLevel o(NULL,0);
	ASObject* ret=NULL;
	thisAndLevel tl=getVm()->getCurObjAndLevel();

	for(it;it!=th->scope_stack.rend();it++)
	{
		if(*it==tl.cur_this)
			tl.cur_this->resetLevel();
		o=(*it)->getVariableByMultiname(*name);
		if(*it==tl.cur_this)
			tl.cur_this->setLevel(tl.cur_level);
		if(o.obj)
		{
			//We have to return the object, not the property
			ret=*it;
			break;
		}
	}
	if(o.obj==NULL)
	{
		LOG(LOG_CALLS, "NOT found, trying Global" );
		o=getGlobal()->getVariableByMultiname(*name);
		if(o.obj)
			ret=getGlobal();
		else
		{
			LOG(LOG_NOT_IMPLEMENTED, "NOT found, pushing Undefined");
			ret=new Undefined;
			//abort();
		}
	}

	assert(ret);
	ret->incRef();
	return ret;
}

ASObject* ABCVm::greaterThan(ASObject* obj1, ASObject* obj2)
{
	LOG(LOG_CALLS,"greaterThan");

	//Real comparision demanded to object
	bool ret=obj1->isGreater(obj2);
	obj1->decRef();
	obj2->decRef();
	return new Boolean(ret);
}

ASObject* ABCVm::greaterEquals(ASObject* obj1, ASObject* obj2)
{
	LOG(LOG_CALLS,"greaterEquals");

	//Real comparision demanded to object
	bool ret=(obj1->isGreater(obj2) || obj1->isEqual(obj2));
	obj1->decRef();
	obj2->decRef();
	return new Boolean(ret);
}

ASObject* ABCVm::lessEquals(ASObject* obj1, ASObject* obj2)
{
	LOG(LOG_CALLS,"lessEquals");

	//Real comparision demanded to object
	bool ret=(obj1->isLess(obj2) || obj1->isEqual(obj2));
	obj1->decRef();
	obj2->decRef();
	return new Boolean(ret);
}

void ABCVm::initProperty(call_context* th, int n)
{
	ASObject* value=th->runtime_stack_pop();
	multiname* name=th->context->getMultiname(n,th);
	ASObject* obj=th->runtime_stack_pop();

	LOG(LOG_CALLS, "initProperty " << *name << ' ' << obj);

	obj->setVariableByMultiname(*name,value);
	obj->decRef();
}

void ABCVm::callSuper(call_context* th, int n, int m)
{
	ASObject** args=new ASObject*[m];
	for(int i=0;i<m;i++)
		args[m-i-1]=th->runtime_stack_pop();

	multiname* name=th->context->getMultiname(n,th); 
	LOG(LOG_CALLS,"callSuper " << *name << ' ' << m);

	ASObject* obj=th->runtime_stack_pop();
	assert(obj->actualPrototype);
	//Store the old prototype
	Class_base* old_prototype=obj->actualPrototype;

	//Move the object protoype and level up
	obj->actualPrototype=old_prototype->super;

	//We modify the cur_level of obj
	obj->decLevel();

	int v=getVm()->method_this_stack.size();

	//We should skip the special implementation of get
	objAndLevel o=obj->getVariableByMultiname(*name, true, false);

	//And the reset it using the stack
	thisAndLevel tl=getVm()->getCurObjAndLevel();
	//What if using [sg]etSuper not on this??
	assert(tl.cur_this==obj);
	tl.cur_this->setLevel(tl.cur_level);

	if(o.obj)
	{
		//If o is already a function call it, otherwise find the Call method
		if(o.obj->getObjectType()==T_FUNCTION)
		{
			IFunction* f=static_cast<IFunction*>(o.obj);
			obj->incRef();
			ASObject* ret=f->fast_call(obj,args,m,o.level);
			th->runtime_stack_push(ret);
		}
		else if(o.obj->getObjectType()==T_UNDEFINED)
		{
			LOG(LOG_NOT_IMPLEMENTED,"We got a Undefined function");
			th->runtime_stack_push(new Undefined);
		}
/*		else if(o->getObjectType()==T_DEFINABLE)
		{
			LOG(LOG_CALLS,"We got a function not yet valid");
			Definable* d=static_cast<Definable*>(o);
			d->define(obj);
			IFunction* f=obj->getVariableByMultiname(*name)->toFunction();
			if(f)
			{
				ASObject* ret=f->fast_call(owner,args,m);
				th->runtime_stack_push(ret);
			}
			else
			{
				LOG(LOG_NOT_IMPLEMENTED,"No such function");
				th->runtime_stack_push(new Undefined);
				//abort();
			}
		}
		else
		{
			//IFunction* f=static_cast<IFunction*>(o->getVariableByQName("Call","",owner));
			//if(f)
			//{
			//	ASObject* ret=f->fast_call(o,args,m);
			//	th->runtime_stack_push(ret);
			//}
			//else
			//{
			//	LOG(LOG_NOT_IMPLEMENTED,"No such function, returning Undefined");
			//	th->runtime_stack_push(new Undefined);
			//}
		}*/
		else
			abort();
	}
	else
	{
		LOG(LOG_NOT_IMPLEMENTED,"Calling an undefined function " << name->name_s);
		th->runtime_stack_push(new Undefined);
	}
	LOG(LOG_CALLS,"End of callSuper " << *name);

	//Reset prototype to its previous value
	assert(obj->actualPrototype==old_prototype->super);
	obj->actualPrototype=old_prototype;

	assert(v==getVm()->method_this_stack.size());
	obj->decRef();
	delete[] args;
}

void ABCVm::callSuperVoid(call_context* th, int n, int m)
{
	ASObject** args=new ASObject*[m];
	for(int i=0;i<m;i++)
		args[m-i-1]=th->runtime_stack_pop();

	multiname* name=th->context->getMultiname(n,th); 
	LOG(LOG_CALLS,"callSuperVoid " << *name << ' ' << m);

	ASObject* obj=th->runtime_stack_pop();

	assert(obj->actualPrototype);
	//Store the old prototype
	Class_base* old_prototype=obj->actualPrototype;

	//Move the object protoype and level up
	obj->actualPrototype=old_prototype->super;

	//We modify the cur_level of obj
	obj->decLevel();

	//We should skip the special implementation of get
	objAndLevel o=obj->getVariableByMultiname(*name, true);

	//And the reset it using the stack
	thisAndLevel tl=getVm()->getCurObjAndLevel();
	//What if using [sg]etSuper not on this??
	assert(tl.cur_this==obj);
	tl.cur_this->setLevel(tl.cur_level);

	if(o.obj)
	{
		//If o is already a function call it, otherwise find the Call method
		if(o.obj->getObjectType()==T_FUNCTION)
		{
			IFunction* f=static_cast<IFunction*>(o.obj);
			obj->incRef();
			f->fast_call(obj,args,m,o.level);
		}
		else if(o.obj->getObjectType()==T_UNDEFINED)
		{
			LOG(LOG_NOT_IMPLEMENTED,"We got a Undefined function");
		}
/*		else if(o->getObjectType()==T_DEFINABLE)
		{
			LOG(LOG_CALLS,"We got a function not yet valid");
			Definable* d=static_cast<Definable*>(o);
			d->define(obj);
			IFunction* f=obj->getVariableByMultiname(*name,owner)->toFunction();
			if(f)
				f->fast_call(owner,args,m);
			else
			{
				LOG(LOG_NOT_IMPLEMENTED,"No such function");
			//	abort();
			}
		}
		else
		{
			//IFunction* f=static_cast<IFunction*>(o->getVariableByQName("Call","",owner));
			//if(f)
			//	f->fast_call(o,args,m);
			//else
			//{
			//	LOG(LOG_NOT_IMPLEMENTED,"No such function, returning Undefined");
			//}
		}*/
		else
			abort();
	}
	else
	{
		LOG(LOG_NOT_IMPLEMENTED,"Calling an undefined function");
	}
	LOG(LOG_CALLS,"End of callSuperVoid " << *name);

	//Reset prototype to its previous value
	assert(obj->actualPrototype==old_prototype->super);
	obj->actualPrototype=old_prototype;

	obj->decRef();
	delete[] args;
}

bool ABCVm::isTypelate(ASObject* type, ASObject* obj)
{
	LOG(LOG_CALLS,"isTypelate");
	bool real_ret=false;

	Class_base* objc=NULL;
	Class_base* c=NULL;
	if(obj->prototype)
	{
		assert(type->getObjectType()==T_CLASS);
		c=static_cast<Class_base*>(type);

		objc=obj->prototype;
	}
	else if(obj->getObjectType()==T_CLASS)
	{
		assert(type->getObjectType()==T_CLASS);
		c=static_cast<Class_base*>(type);

		//Special case for Class
		if(c->class_name=="Class")
		{
			type->decRef();
			return obj;
		}
		objc=static_cast<Class_base*>(obj);
	}
	else
	{
		//Special cases
		if(obj->getObjectType()==T_FUNCTION && type==Class_function::getClass())
			return true;

		real_ret=obj->getObjectType()==type->getObjectType();
		LOG(LOG_CALLS,"isTypelate on non classed object " << real_ret);
		if(real_ret==false)
		{
			//TODO: obscene hack, check casting of stuff
			if(obj->getObjectType()==T_INTEGER && type->getObjectType()==T_NUMBER)
			{
				cout << "HACK for Integer" << endl;
				real_ret=true;
			}
		}
		obj->decRef();
		type->decRef();
		return real_ret;
	}

	real_ret=objc->isSubClass(c);
	LOG(LOG_CALLS,"Type " << objc->class_name << " is " << ((real_ret)?" ":"not ") 
			<< "subclass of " << c->class_name);
	obj->decRef();
	type->decRef();
	return real_ret;
}

ASObject* ABCVm::asTypelate(ASObject* type, ASObject* obj)
{
	LOG(LOG_CALLS,"asTypelate");
	assert(obj->getObjectType()!=T_FUNCTION);

	assert(type->getObjectType()==T_CLASS);
	Class_base* c=static_cast<Class_base*>(type);

	Class_base* objc;
	if(obj->prototype)
		objc=obj->prototype;
	else if(obj->getObjectType()==T_CLASS)
	{
		//Special case for Class
		if(c->class_name=="Class")
		{
			type->decRef();
			return obj;
		}
		
		objc=static_cast<Class_base*>(obj);
	}
	else
	{
		obj->decRef();
		type->decRef();
		return new Null;
	}

	bool real_ret=objc->isSubClass(c);
	LOG(LOG_CALLS,"Type " << objc->class_name << " is " << ((real_ret)?" ":"not ") 
			<< "subclass of " << c->class_name);
	type->decRef();
	if(real_ret)
		return obj;
	else
	{
		obj->decRef();
		return new Null;
	}
}

bool ABCVm::ifEq(ASObject* obj1, ASObject* obj2)
{
	bool ret=obj1->isEqual(obj2);
	LOG(LOG_CALLS,"ifEq (" << ((ret)?"taken)":"not taken)"));

	//Real comparision demanded to object
	obj1->decRef();
	obj2->decRef();
	return ret;
}

bool ABCVm::ifStrictEq(ASObject* obj2, ASObject* obj1)
{
	LOG(LOG_CALLS,"ifStrictEq");
	if(obj1->getObjectType()!=obj2->getObjectType())
		return false;
	return ifEq(obj2,obj1);
}

bool ABCVm::ifStrictNE(ASObject* obj2, ASObject* obj1)
{
	LOG(LOG_CALLS,"ifStrictNE");
	return !ifStrictEq(obj2,obj1);
}

bool ABCVm::in(ASObject* val2, ASObject* val1)
{
	LOG(LOG_CALLS, "in" );
	bool ret=val2->hasPropertyByQName(val1->toString(),"");
	val1->decRef();
	val2->decRef();
	return ret;
}

bool ABCVm::ifFalse(ASObject* obj1)
{
	bool ret=!Boolean_concrete(obj1);
	LOG(LOG_CALLS,"ifFalse (" << ((ret)?"taken":"not taken") << ')');

	obj1->decRef();
	return ret;
}

void ABCVm::constructProp(call_context* th, int n, int m)
{
	arguments args(m);
	for(int i=0;i<m;i++)
		args.set(m-i-1,th->runtime_stack_pop());

	multiname* name=th->context->getMultiname(n,th);

	LOG(LOG_CALLS,"constructProp "<< *name << ' ' << m);

	ASObject* obj=th->runtime_stack_pop();

	thisAndLevel tl=getVm()->getCurObjAndLevel();
	if(tl.cur_this==obj)
		obj->resetLevel();

	ASObject* o=obj->getVariableByMultiname(*name).obj;

	if(tl.cur_this==obj)
		obj->setLevel(tl.cur_level);

	if(o==NULL)
	{
		LOG(LOG_ERROR,"Could not resolve property");
		abort();
	}

	//The get protocol expects that we incRef the var
	o->incRef();

	if(o->getObjectType()==T_DEFINABLE)
	{
		LOG(LOG_CALLS,"Deferred definition of property " << *name);
		Definable* d=static_cast<Definable*>(o);
		d->define(obj);
		o=obj->getVariableByMultiname(*name).obj;
		LOG(LOG_CALLS,"End of deferred definition of property " << *name);
	}

	LOG(LOG_CALLS,"Constructing");
	ASObject* ret;
	if(o->getObjectType()==T_CLASS)
	{
		Class_base* o_class=static_cast<Class_base*>(o);
		ret=o_class->getInstance(true,&args)->obj;
	}
	else if(o->getObjectType()==T_FUNCTION)
	{
		SyntheticFunction* sf=dynamic_cast<SyntheticFunction*>(o);
		assert(sf);
		ret=new ASObject;
		if(sf->mi->body)
		{
			LOG(LOG_CALLS,"Building method traits");
			for(int i=0;i<sf->mi->body->trait_count;i++)
				th->context->buildTrait(ret,&sf->mi->body->traits[i],false);
			ret->incRef();
			assert(sf->closure_this==NULL);
			sf->call(ret,&args,0);

			//Let's see if an AS prototype has been defined on the function
			ASObject* asp=sf->getVariableByQName("prototype","").obj;
			if(asp)
				asp->incRef();

			//Now add our prototype
			sf->incRef();
			ret->prototype=new Class_function(sf,asp);
		}
	}
	else
		abort();

	th->runtime_stack_push(ret);
	obj->decRef();
	LOG(LOG_CALLS,"End of constructing " << ret);
}

bool ABCVm::hasNext2(call_context* th, int n, int m)
{
	LOG(LOG_CALLS,"hasNext2 " << n << ' ' << m);
	ASObject* obj=th->locals[n];
	int cur_index=th->locals[m]->toInt();

	if(obj->implementation)
	{
		bool ret;
		//cur_index is modified with the next index
		if(obj->implementation->hasNext(cur_index,ret))
		{
			if(ret)
			{
				th->locals[m]->decRef();
				th->locals[m]=new Integer(cur_index);
			}
			else
			{
				th->locals[n]->decRef();
				th->locals[n]=new Null;
				th->locals[m]->decRef();
				th->locals[m]=new Integer(0);
			}
			return ret;
		}
	}

/*	//Look up if there is a following index which is still an object
	//(not a method)
	for(cur_index;cur_index<obj->numVariables();cur_index++)
	{
		obj_var* var=obj->Variables.getValueAt(cur_index);
		if(var->var && var->var->getObjectType()!=T_FUNCTION)
			break;
	}*/

	//Our references are 0 based, the AS ones are 1 based
	//what a mess
	if(cur_index<obj->numVariables())
	{
		th->locals[m]->decRef();
		th->locals[m]=new Integer(cur_index+1);
		return true;
	}
	else
	{
		th->locals[n]->decRef();
		th->locals[n]=new Null;
		th->locals[m]->decRef();
		th->locals[m]=new Integer(0);
		return false;
	}
}

void ABCVm::newObject(call_context* th, int n)
{
	LOG(LOG_CALLS,"newObject " << n);
	ASObject* ret=new ASObject;
	for(int i=0;i<n;i++)
	{
		ASObject* value=th->runtime_stack_pop();
		ASObject* name=th->runtime_stack_pop();
		ret->setVariableByQName(name->toString(),"",value);
		name->decRef();
	}

	th->runtime_stack_push(ret);
}

void ABCVm::getDescendants(call_context* th, int n)
{
	abort();
/*	LOG(LOG_CALLS,"newObject " << n);
	ASObject* ret=new ASObject;
	for(int i=0;i<n;i++)
	{
		ASObject* value=th->runtime_stack_pop();
		ASObject* name=th->runtime_stack_pop();
		ret->setVariableByQName(name->toString(),"",value);
		name->decRef();
	}

	th->runtime_stack_push(ret);*/
}

uintptr_t ABCVm::increment_i(ASObject* o)
{
	LOG(LOG_CALLS,"increment_i");

	int n=o->toInt();
	o->decRef();
	return n+1;
}

ASObject* ABCVm::nextValue(ASObject* index, ASObject* obj)
{
	LOG(LOG_CALLS,"nextValue");
	if(index->getObjectType()!=T_INTEGER)
	{
		LOG(LOG_ERROR,"Type mismatch");
		abort();
	}

	ASObject* ret=NULL;
	if(obj->implementation)
	{ 
		if(obj->implementation->nextValue(index->toInt()-1,ret))
		{
			obj->decRef();
			index->decRef();
			ret->incRef();
			return ret;
		}
	}

	ret=obj->getValueAt(index->toInt()-1);
	obj->decRef();
	index->decRef();
	ret->incRef();
	return ret;
}

ASObject* ABCVm::nextName(ASObject* index, ASObject* obj)
{
	LOG(LOG_CALLS,"nextName");
	if(index->getObjectType()!=T_INTEGER)
	{
		LOG(LOG_ERROR,"Type mismatch");
		abort();
	}

	ASObject* ret=NULL;
	if(obj->implementation)
	{ 
		if(obj->implementation->nextName(index->toInt()-1,ret))
		{
			obj->decRef();
			index->decRef();
			return ret;
		}
	}

	ret=Class<ASString>::getInstanceS(true,obj->getNameAt(index->toInt()-1))->obj;
	obj->decRef();
	index->decRef();
	return ret;
}

void ABCVm::newClass(call_context* th, int n)
{
	LOG(LOG_CALLS, "newClass " << n );
	method_info* constructor=&th->context->methods[th->context->instances[n].init];
	int name_index=th->context->instances[n].name;
	assert(name_index);
	const multiname* mname=th->context->getMultiname(name_index,NULL);

	Class_base* ret=new Class_inherit(mname->name_s);
	ASObject* tmp=th->runtime_stack_pop();

	assert(th->context);
	ret->context=th->context;

	//Null is a "valid" base class
	if(tmp->getObjectType()!=T_NULL)
	{
		assert(tmp->getObjectType()==T_CLASS);
		ret->super=static_cast<Class_base*>(tmp);
		ret->max_level=ret->super->max_level+1;
		ret->setLevel(ret->max_level);
	}

	method_info* m=&th->context->methods[th->context->classes[n].cinit];
	SyntheticFunction* cinit=new SyntheticFunction(m);
	//cinit must inherit the current scope
	cinit->acquireScope(th->scope_stack);
	//and the created class
	cinit->addToScope(ret);


	LOG(LOG_CALLS,"Building class traits");
	for(int i=0;i<th->context->classes[n].trait_count;i++)
	{
		//When we build the traits we set the prototype to itself, so the level is correctly found
		ret->actualPrototype=ret;
		th->context->buildTrait(ret,&th->context->classes[n].traits[i],false);
		//Then we clean away this HACK
		ret->actualPrototype=NULL;
	}

	//add Constructor the the class methods
	ret->constructor=new SyntheticFunction(constructor);
	ret->class_index=n;

	//Add protected namespace if needed
	if((th->context->instances[n].flags)&0x08)
	{
		ret->use_protected=true;
		int ns=th->context->instances[n].protectedNs;
		ret->protected_ns=th->context->getString(th->context->constant_pool.namespaces[ns].name);
	}

	//add implemented interfaces
	for(int i=0;i<th->context->instances[n].interface_count;i++)
	{
		multiname* name=th->context->getMultiname(th->context->instances[n].interfaces[i],NULL);
		ret->addImplementedInterface(*name);

		//Make the class valid if needed
		ASObject* obj=getGlobal()->getVariableByMultiname(*name).obj;

		//Named only interfaces seems to be allowed 
		if(obj==NULL)
			continue;

		if(obj->getObjectType()==T_DEFINABLE)
		{
			LOG(LOG_CALLS,"Class " << *name << " is not yet valid (as interface)");
			Definable* d=static_cast<Definable*>(obj);
			d->define(getGlobal());
			LOG(LOG_CALLS,"End of deferred init of class " << *name);
			obj=getGlobal()->getVariableByMultiname(*name).obj;
			assert(obj);
		}
	}

	LOG(LOG_CALLS,"Calling Class init " << ret);
	ret->incRef();
	//Class init functions are called with global as this
	cinit->call(ret,NULL,ret->max_level);
	LOG(LOG_CALLS,"End of Class init " << ret);
	th->runtime_stack_push(ret);
}

void ABCVm::swap()
{
	LOG(LOG_CALLS,"swap");
}

ASObject* ABCVm::newActivation(call_context* th,method_info* info)
{
	LOG(LOG_CALLS,"newActivation");
	//TODO: Should create a real activation object
	//TODO: Should method traits be added to the activation context?
	ASObject* act=new ASObject;
	for(int i=0;i<info->body->trait_count;i++)
		th->context->buildTrait(act,&info->body->traits[i],false);

	return act;
}

void ABCVm::popScope(call_context* th)
{
	LOG(LOG_CALLS,"popScope");
	th->scope_stack.back()->decRef();
	th->scope_stack.pop_back();
}

ASObject* ABCVm::lessThan(ASObject* obj1, ASObject* obj2)
{
	LOG(LOG_CALLS,"lessThan");

	//Real comparision demanded to object
	bool ret=obj1->isLess(obj2);
	obj1->decRef();
	obj2->decRef();
	return new Boolean(ret);
}

void ABCVm::call(call_context* th, int m)
{
	arguments args(m);
	for(int i=0;i<m;i++)
		args.set(m-i-1,th->runtime_stack_pop());

	ASObject* obj=th->runtime_stack_pop();
	ASObject* f=th->runtime_stack_pop();
	LOG(LOG_CALLS,"call " << m << ' ' << f);

	if(f->getObjectType()==T_FUNCTION)
	{
		IFunction* func=static_cast<IFunction*>(f);
		//TODO: check for correct level, member function are already binded
		ASObject* ret=func->call(obj,&args,0);
		//Push the value only if not null
		if(ret)
			th->runtime_stack_push(ret);
		else
			th->runtime_stack_push(new Undefined);
		obj->decRef();
		f->decRef();
	}
	else
	{
		LOG(LOG_NOT_IMPLEMENTED,"Function not good");
		th->runtime_stack_push(new Undefined);
	}
	LOG(LOG_CALLS,"End of call " << m << ' ' << f);

}

void ABCVm::deleteProperty(call_context* th, int n)
{
	multiname* name=th->context->getMultiname(n,th); 
	LOG(LOG_NOT_IMPLEMENTED,"deleteProperty " << *name);
	ASObject* obj=th->runtime_stack_pop();
	obj->deleteVariableByMultiname(*name);

	//Now we assume thta all objects are dynamic
	th->runtime_stack_push(abstract_b(true));

	obj->decRef();
}

ASObject* ABCVm::newFunction(call_context* th, int n)
{
	LOG(LOG_CALLS,"newFunction " << n);

	method_info* m=&th->context->methods[n];
	SyntheticFunction* f=new SyntheticFunction(m);
	f->func_scope=th->scope_stack;
	for(int i=0;i<f->func_scope.size();i++)
		f->func_scope[i]->incRef();

	//Bind the function to null, as this is not a class method
	f->bind(NULL,-1);
	return f;
}

ASObject* ABCVm::getScopeObject(call_context* th, int n)
{
	ASObject* ret=th->scope_stack[n];
	ret->incRef();
	LOG(LOG_CALLS, "getScopeObject: " << ret );
	return ret;
}

ASObject* ABCVm::pushString(call_context* th, int n)
{
	tiny_string s=th->context->getString(n); 
	LOG(LOG_CALLS, "pushString " << s );
	return Class<ASString>::getInstanceS(true,s)->obj;
}

ASObject* ABCVm::newCatch(call_context* th, int n)
{
	LOG(LOG_NOT_IMPLEMENTED,"newCatch " << n);
	return new Undefined;
}

void ABCVm::newArray(call_context* th, int n)
{
	LOG(LOG_CALLS, "newArray " << n );
	Array* ret=Class<Array>::getInstanceS(true);
	ret->resize(n);
	for(int i=0;i<n;i++)
		ret->set(n-i-1,th->runtime_stack_pop());

	th->runtime_stack_push(ret->obj);
}

