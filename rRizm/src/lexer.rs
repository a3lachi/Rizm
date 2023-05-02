


pub mod lexer {
    pub struct Lexer {
        pub value: i32,
    }

    impl Lexer {
        pub fn new(val: i32) -> Self {
            Lexer { value: val }
        }

        pub fn increment(&mut self) {
            self.value += 1;
        }

        pub fn print(&self) {
            println!("Value");
        }
    }
}