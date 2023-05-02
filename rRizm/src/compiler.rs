
#[path = "./lexer.rs"]
mod lexer;

pub mod compiler {
    

    
    pub struct Compiler {
        pub value: i32,
    }

    impl Compiler {
        pub fn new(val: i32) -> Self {
            println!("[x] - NEW COMPILER");
            Compiler { value: val }
        }
        pub fn compile() {
            let x:i32 = 6 ;
            let mut y = lexer::lexer::Lexer::new(56);
            println!("[x] - COMPILER STARTED COMPILING");
            // let mut obj = lexer::lexer::Lexer::new(10);
            // obj.increment();
            // obj.print();
        }

    }
}