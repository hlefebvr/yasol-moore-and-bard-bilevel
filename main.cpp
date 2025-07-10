#include <iostream>
#include "Datastructures/qlp/Qlp.hpp"
#include "Algorithms/Algorithms.hpp"

#include <vector>
#include <string>

using namespace std;

data::Qlp build_qlp() {

    std::vector<data::QpVar> variables {
        data::QpVar("x", 0, 0.0, 10.0,  data::QpVar::generals, data::QpVar::exists),
        data::QpVar("y", 1, 0.0, 10.0,  data::QpVar::generals, data::QpVar::exists),
        data::QpVar("y_bar", 2, 0.0, 10.0,  data::QpVar::generals, data::QpVar::all)
    };

    data::QpObjFunc objective(data::QpObjFunc::min);
    objective.setSize(3);
    objective.setObjElement(0, -1);
    objective.setObjElement(1, -10);
    objective.setObjElement(2, 0);

    data::QpSparseMatrix matrix;
    std::vector<data::QpRhs> rhs;

    {
        // -25 * x + 20 * y <= 30
        std::vector<data::IndexedElement> r1;
        r1.emplace_back(0, -25);
        r1.emplace_back(1, 20);
        matrix.push_back(r1);

        rhs.emplace_back(30, data::QpRhs::smallerThanOrEqual);

        // x + 2 * y <= 10
        std::vector<data::IndexedElement> r2;
        r2.emplace_back(0, 1);
        r2.emplace_back(1, 2);
        matrix.push_back(r2);

        rhs.emplace_back(10, data::QpRhs::smallerThanOrEqual);

        // 2 * x - y <= 15
        std::vector<data::IndexedElement> r3;
        r3.emplace_back(0, 2);
        r3.emplace_back(1, -1);
        matrix.push_back(r3);

        rhs.emplace_back(15, data::QpRhs::smallerThanOrEqual);

        // 2 * x + 10 * y >= 15
        std::vector<data::IndexedElement> r4;
        r4.emplace_back(0, 2);
        r4.emplace_back(1, 10);
        matrix.push_back(r4);

        rhs.emplace_back(15, data::QpRhs::greaterThanOrEqual);
    }

    {
        // -25 * x + 20 * y <= 30
        std::vector<data::IndexedElement> r1;
        r1.emplace_back(0, -25);
        r1.emplace_back(2, 20);
        matrix.push_back(r1);

        rhs.emplace_back(data::QpNum(30), data::QpRhs::smallerThanOrEqual);
        rhs.back().setResponsibility(data::Constraint::UNIVERSAL);

        // x + 2 * y <= 10
        std::vector<data::IndexedElement> r2;
        r2.emplace_back(0, 1);
        r2.emplace_back(2, 2);
        matrix.push_back(r2);

        rhs.emplace_back(data::QpNum(10), data::QpRhs::smallerThanOrEqual);
        rhs.back().setResponsibility(data::Constraint::UNIVERSAL);

        // 2 * x - y <= 15
        std::vector<data::IndexedElement> r3;
        r3.emplace_back(0, 2);
        r3.emplace_back(2, -1);
        matrix.push_back(r3);

        rhs.emplace_back(data::QpNum(15), data::QpRhs::smallerThanOrEqual);
        rhs.back().setResponsibility(data::Constraint::UNIVERSAL);

        // 2 * x + 10 * y >= 15
        std::vector<data::IndexedElement> r4;
        r4.emplace_back(0, 2);
        r4.emplace_back(2, 10);
        matrix.push_back(r4);

        rhs.emplace_back(data::QpNum(15), data::QpRhs::greaterThanOrEqual);
        rhs.back().setResponsibility(data::Constraint::UNIVERSAL);
    }

    // y - y_bar <= 0
    std::vector<data::IndexedElement> r5;
    r5.emplace_back(1, 1);
    r5.emplace_back(2, -1);
    matrix.push_back(r5);

    rhs.emplace_back(data::QpNum(0), data::QpRhs::smallerThanOrEqual);

    data::Qlp qlp(objective,variables, matrix, rhs);

    std::cout << qlp.toString() << std::endl;

    return qlp;
}


int main() {

    auto qlp = build_qlp();

    const std::string LOG_TAG = "QlpSolver";
    algorithm::Algorithm::AlgorithmType alg = algorithm::Algorithm::nested_benders;
    algorithm::Algorithm::SolutionCase sc = algorithm::Algorithm::WORST_CASE;
    algorithm::Algorithm::QlpSolution s;

    if (alg == algorithm::Algorithm::dep) {
        utils::Logger::globalLog(utils::LOG_INFO, LOG_TAG, "Algorithm: CPLEX");
        utils::Timer t;
        utils::Logger::globalLog(utils::LOG_INFO, LOG_TAG, "Initializing...");
        algorithm::Qlp2Lp alg(qlp);
        utils::Logger::globalLog(utils::LOG_INFO, LOG_TAG, "Solving...");
        s=alg.solveQlp(sc);
        t.stop();
        utils::Logger::globalLog(utils::LOG_INFO, LOG_TAG, "Finished. Time (s) : " + utils::ToolBox::convertToString(t.getSeconds()));
        utils::Logger::globalLog(utils::LOG_INFO, LOG_TAG, "Obj. Func. Value   : " + s.getObjFunctionValue().toString());
        utils::Logger::globalLog(utils::LOG_INFO, LOG_TAG, "Variable allocation: " + data::QpNum::vecToStringSparse(s.getSolutionVector()));

    } else {
        utils::Logger::globalLog(utils::LOG_INFO, LOG_TAG, "Algorithm: Nested Benders Decomposition");
        utils::Logger::globalLog(utils::LOG_INFO, LOG_TAG, "Solving...");
        utils::Timer t;
        algorithm::NbdMaster nbd(qlp);
        s=nbd.solveQlp(sc);
        t.stop();
        utils::Logger::globalLog(utils::LOG_INFO, LOG_TAG, "Finished. Time (s) : " + utils::ToolBox::convertToString(t.getSeconds()));
        utils::Logger::globalLog(utils::LOG_INFO, LOG_TAG, "Obj. Func. Value   : " + s.getObjFunctionValue().toString());
        //TODO
        utils::Logger::globalLog(utils::LOG_INFO, LOG_TAG, "Variable allocation: " + data::QpNum::vecToStringSparse(s.getSolutionVector()));
        //utils::Logger::globalLog(utils::LOG_INFO, LOG_TAG, "Cut: "+
        //		nbd.getFirstStageBendersCuts()[0].toString());

    }

    std::cout << s.getSolutionStatusString() << std::endl;
    std::cout << s.getObjFunctionValue() << std::endl;

}
