#ifndef POS_SYM_LIN_SYSTEM_H
#define POS_SYM_LIN_SYSTEM_H

#include "../include/linear.h"

class PosSymLinSystem : public LinearSystem {
public:
    PosSymLinSystem() = delete;
    PosSymLinSystem(const Matrix& A, const Vector& b);

    virtual Vector Solve() const override;

private:
    bool IsSymmetric() const;
};

#endif