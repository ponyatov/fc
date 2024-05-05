module test

open NUnit.Framework

[<SetUp>]
let Setup () = ()

[<Test>]
let pass () = Assert.Pass()

// [<Test>]
// let fail () = Assert.Fail()

open fc

[<Test>]
let i123 () =
    Assert.AreEqual(Int 123, i123)
    Assert.AreEqual(eval (i123), 123)

[<Test>]
let add12 () =
    Assert.AreEqual(add12, Op("+", Int 1, Int 2))
    Assert.AreEqual(eval (add12), 3)
    Assert.AreEqual(eval (Op("*", Int 2, Int 3)), 6)

[<Test>]
let vasd () =
    Assert.AreEqual(vasd, Var "asd")
    Assert.AreEqual(lookup env "pi", 3)

module Stub =
    [<EntryPoint>]
    let main _ = 0
