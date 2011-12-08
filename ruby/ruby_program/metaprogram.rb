class Object
	def bindings
		binding;
	end
end

class Meta
	attr_accessor :x;
	def initialize(num)
		@x = num;
	end
end

def add_method(obj, func, &block)
	obj.class_eval {
		define_method(func, &block);
	}
end

def add_single(class_obj, func, &block)
	eig = class << class_obj; self; end;
	eig.class_eval {
		define_method(func, &block);
	}
end
