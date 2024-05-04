module test

open NUnit.Framework

[<SetUp>]
let Setup () = ()

[<Test>]
let pass () = Assert.Pass()

// [<Test>]
// let fail () = Assert.Fail

[<Test>]
let i123 () = Assert.AreEqual(fc.Int 123, fc.i123)


module Program =
    [<EntryPoint>]
    let main _ = 0
