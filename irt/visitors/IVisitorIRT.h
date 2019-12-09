#pragma once

// ToDo Include IExp IStm
namespace IrtTree {

    // expressions
    	class ConstExp;
	class NameExp;
	class TempExp;
	class BinaryExp;
	class MemoryExp;
	class CallExp;
	class ESeqExp;
    // statements
    	class MoveStm;
    	class ExpStm;
    	class JumpStm;
    	class CJumpStm;
    	class SeqStm;
    	class LabelStm;

	class IVisitor {
    public:
			IVisitor() = default;

            		virtual void Visit( const ConstExp* n ) = 0;
			virtual void Visit( const NameExp* n ) = 0;
			virtual void Visit( const TempExp* n ) = 0;
			virtual void Visit( const BinaryExp* n ) = 0;
			virtual void Visit( const MemoryExp* n ) = 0;
			virtual void Visit( const CallExp* n ) = 0;
			virtual void Visit( const ESeqExp* n ) = 0;

			virtual void Visit( const MoveStm* n ) = 0;
			virtual void Visit( const ExpStm* n ) = 0;
			virtual void Visit( const JumpStm* n ) = 0;
			virtual void Visit( const CJumpStm* n ) = 0;
			virtual void Visit( const SeqStm* n ) = 0;
			virtual void Visit( const LabelStm* n ) = 0;

    };
};