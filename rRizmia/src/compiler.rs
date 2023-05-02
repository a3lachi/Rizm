mod lexer;



// #[allow(dead_code)]
// fn compile() {
//     let x:i32 = 6 ;
//     println!("[x] - COMPILER STARTED COMPILING");
// }




fn main() {
    println!("[x] - STARTING CRATE COMPILER");
    let mut obj = lexer::lexer::Lexer::new(10);
    obj.increment();
    obj.print();
}