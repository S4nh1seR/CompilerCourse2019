#pragma once

//#include <Visitor.h> toDo: Подключить visitor

namespace IrtTree {

	class IExp {
	public:
	    virtual ~IExp() = default;
	    virtual void AcceptVisitor(IVisitor* visitor) const = 0;
	};

}

